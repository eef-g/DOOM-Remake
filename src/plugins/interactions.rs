use bevy::{prelude::*, window::PrimaryWindow, input::mouse::MouseButtonInput};
use bevy_rapier2d::prelude::*;

pub struct InteractionPlugin;

impl Plugin for InteractionPlugin {
    fn build(&self, app: &mut App) {
        app.add_systems(Startup, spawn_grid_highlight);
        app.add_systems(Update, (
            mouse_button_events,
            highlight_selected_grid
        ));
    }
}

#[derive(Component)]
pub struct SelectSquare{}

pub fn spawn_grid_highlight(
    mut commands: Commands,
    asset_server: Res<AssetServer>
) {
    let texture = asset_server.load("selection.png");
    commands.spawn((
        SpriteBundle {
            texture,
            ..default()
        },
        SelectSquare{},
        Name::new("SelectSquare")
    ));
}

// Showing selected grid square
pub fn highlight_selected_grid(
    q_windows: Query<&Window, With<PrimaryWindow>>,
    camera_q: Query<(&Camera, &GlobalTransform)>,
    mut cursor_event: EventReader<CursorMoved>,
    mut select_q: Query<(&SelectSquare, &mut Transform)>
) {
    let (camera, camera_transform) = camera_q.single();
    if let Some(position) = q_windows.single().cursor_position()
        .and_then(|cursor| camera.viewport_to_world_2d(camera_transform, cursor)) {
        for _ in cursor_event.iter() {
            let translated_pos = mouse_to_grid_pos(Vec2::new(position.x, position.y));
            for (_, mut transform) in &mut select_q {
                transform.translation = Vec3::new(translated_pos.x, translated_pos.y, 0.0);
            }
        }
    }
}

// Mining mechanics
pub fn mouse_button_events(
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
    let mut new_x = ( (mouse_pos.x / 16.0) as i32 ) as f32 * 16.0;
    let mut new_y = ( (mouse_pos.y / 16.0) as i32 ) as f32 * 16.0;
    let x_mod = mouse_pos.x as i32 % 16;
    let y_mod = mouse_pos.y as i32 % 16;

    if x_mod >= 8 {
        new_x += 16.0; 
    } 
    if y_mod > 8 {
        new_y += 16.0;
    }

    return Vec2::new(new_x, new_y);
}
