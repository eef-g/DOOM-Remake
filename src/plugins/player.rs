use bevy::{prelude::*, render::camera::ScalingMode};


pub struct PlayerPlugin;

impl Plugin for PlayerPlugin{
    fn build(&self, app: &mut App) {
        app
            .add_systems(Startup, spawn_player)
            .add_systems(Update, player_movement)
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
    // Now spawn a SpriteBundle -- This is a collection of components that let us use a sprite
    commands.spawn(( // We have 2 parenthesis here since if we want multiple components then we
        // pass in a tuple of the components to the spawn function
        SpriteBundle {
            sprite: Sprite { ..default() },
            texture,
            ..default()
        },
        Player{
            speed: 100.0,
        }
    ))
    // Add the camera as a child so that way it automatically follows the player
    .with_children(|parent| {
        parent.spawn(main_camera);
    });
}

pub fn player_movement(
    mut characters: Query<(&mut Transform, &Player, &mut Sprite)>,
    input: Res<Input<KeyCode>>,
    time: Res<Time>,
) {
    for (mut transform, player, mut sprite) in &mut characters {
        let move_amount = player.speed * time.delta_seconds();
        if input.pressed(KeyCode::W) {
            transform.translation.y += move_amount;
        }
        if input.pressed(KeyCode::S) {
            transform.translation.y -= move_amount;
        }
        if input.pressed(KeyCode::D) {
            transform.translation.x += move_amount;
            sprite.flip_x = false;
            
        }
        if input.pressed(KeyCode::A) {
            transform.translation.x -= move_amount;
            sprite.flip_x = true;
        }
    }
}

