use bevy::{prelude::*, render::camera::ScalingMode, window::PrimaryWindow, input::mouse::MouseButtonInput};
use bevy_rapier2d::prelude::*;

pub struct PlayerPlugin;

impl Plugin for PlayerPlugin{
    fn build(&self, app: &mut App) {
        app
            .add_systems(Startup, spawn_player)
            .add_systems(Update, (
                player_movement,
                mouse_button_events
            ))
            .insert_resource(Money(100.0));
    }
}

// Components
#[derive(Component)]
pub struct Player {
    pub speed: f32,
}


// Resources
#[derive(Resource)]
pub struct Money(pub f32);


// Systems
pub fn spawn_player(mut commands: Commands, asset_server: Res<AssetServer>) {
    // Spawn a camera that lets us actually treat this like a game
    let mut main_camera = Camera2dBundle::default();
    let default_width = 256.00;
    let default_height = 144.00;
    main_camera.projection.scaling_mode = ScalingMode::AutoMin{ 
        min_width: default_width * 2.5,
        min_height: default_height * 2.5
    }; 
    let texture = asset_server.load("character.png");
    let pos_x = Vec3::new(100.0, 0.0, 0.5);
    let pos_y = Vec3::new(0.0, 50.0, 0.5);
    // Now spawn a SpriteBundle -- This is a collection of components that let us use a sprite
    commands.spawn(( // We have 2 parenthesis here since if we want multiple components then we
        // pass in a tuple of the components to the spawn function
        RigidBody::KinematicPositionBased,
        Collider::capsule(Vec2::new(0.0, 0.0), Vec2::new(0.0, 2.0), 5.0),
        KinematicCharacterController::default(),
        SpriteBundle {
            sprite: Sprite { ..default() },
            texture,
            transform: Transform {
                translation: pos_x + pos_y,
                ..default()
            },
            ..default()
        },
        Player{
            speed: 100.0,
        },
        Name::new("Player")
    ))
    // Add the camera as a child so that way it automatically follows the player
    .with_children(|parent| {
        parent.spawn(main_camera);
    });
}
//
// pub fn player_movement(
//     mut characters: Query<(&mut Transform, &Player, &mut Sprite, &mut Mob)>,
//     wall_query: Query<&Transform, (With<TileCollider>, Without<Mob>)>,
//     input: Res<Input<KeyCode>>,
//     time: Res<Time>,
// ) {
//     for (mut transform, player, mut sprite, mut mob) in &mut characters {
//         let move_amount = player.speed * time.delta_seconds();
//         let mut delta_x = 0.0;
//         let mut delta_y = 0.0;
//
//         if input.pressed(KeyCode::W) {
//             delta_y += move_amount;
//         }
//         if input.pressed(KeyCode::S) {
//             delta_y -= move_amount;
//         }
//         if input.pressed(KeyCode::D) {
//             delta_x += move_amount;
//             sprite.flip_x = false;
//             
//         }
//         if input.pressed(KeyCode::A) {
//             delta_x -= move_amount;
//             sprite.flip_x = true;
//         }
//         move_mob(&wall_query, &mut transform, &mut mob, delta_x, delta_y);
//     }
// }
pub fn player_movement(
    mut controllers: Query<( &mut KinematicCharacterController, &mut Sprite, &Player)>,
    time: Res<Time>,
    input: Res<Input<KeyCode>>
) {
    for (mut controller, mut sprite, player) in controllers.iter_mut() {
        let move_amount =  player.speed * time.delta_seconds();
        let mut delta_x = 0.0;
        let mut delta_y = 0.0;

        if input.pressed(KeyCode::W) {
            delta_y += move_amount;
        }
        if input.pressed(KeyCode::S) {
            delta_y -= move_amount;
        }
        if input.pressed(KeyCode::D) {
            delta_x += move_amount;
            sprite.flip_x = false;
            
        }
        if input.pressed(KeyCode::A) {
            delta_x -= move_amount;
            sprite.flip_x = true;
        }
        controller.translation = Some(Vec2::new(delta_x, delta_y));
    }

}

// Mining mechanics
fn mouse_button_events(
    mut mousebtn_evr: EventReader<MouseButtonInput>,
    q_windows: Query<&Window, With<PrimaryWindow>>,
    camera_q: Query<(&Camera, &GlobalTransform)>,
    rapier_context: Res<RapierContext>,
    asset_server: Res<AssetServer>,
    mut commands: Commands
) {
    use bevy::input::ButtonState;

    for ev in mousebtn_evr.iter() {
        match ev.state {
            ButtonState::Pressed => {
                let filter = QueryFilter::default();
                let (camera, camera_transform) = camera_q.single();
                let Some(mouse_position) = q_windows.single().cursor_position()
                    .and_then(|cursor| camera.viewport_to_world_2d(camera_transform, cursor))
                else {
                    return 
                };
                rapier_context.intersections_with_point(mouse_position, filter, |entity| {
                    let Some(mut entity_commands) = commands.get_entity(entity) else { todo!() }; {
                        entity_commands.remove::<SpriteBundle>();
                        entity_commands.remove::<Collider>();
                        let texture = asset_server.load("ground.png");
                        let new_translation = mouse_to_grid_pos(mouse_position);
                        println!("{:?}", new_translation);
                        entity_commands.insert(SpriteBundle {
                            texture,
                            transform: Transform {
                                translation: Vec3::new(new_translation.x, new_translation.y, 0.0),
                                ..default()
                            },
                            ..default()
                        });
                    }
                    // Return `false` instead if we want to stop searching for other colliders containing this point.
                    true
                });
            }
            ButtonState::Released => {
                println!("Mouse button release: {:?}", ev.button);
            }
        }
    }
}


pub fn mouse_to_grid_pos(mouse_pos: Vec2) -> Vec2{
    println!("Input position: {:?}", mouse_pos);
    let new_x = ( (mouse_pos.x / 16.0) as i32 ) as f32 * 16.0;
    let new_y = ( (mouse_pos.y / 16.0) as i32 ) as f32 * 16.0;

    return Vec2::new(new_x, new_y);
}
