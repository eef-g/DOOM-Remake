use bevy::prelude::*;
use bevy_rapier2d::prelude::*;

mod plugins;
mod tests;

fn main() {
    App::new()
        // Making ImagePlugin to default_nearest allows sprites to keep their resolution
        .add_plugins(DefaultPlugins
            .set(ImagePlugin::default_nearest())
            .set(WindowPlugin {
                primary_window: Some(Window {
                    title: "The Isle".into(),
                    resolution: (640.0, 480.0).into(),
                    resizable: false,
                    ..default()
                }),
                ..default()
            })
            .build(),
        )
        .add_plugins((
            // Add physics to the Game
            RapierPhysicsPlugin::<NoUserData>::pixels_per_meter(16.0),
            // Debug plugin goes first -- comment out if not wanting to debug
            plugins::DebugPlugin,

            // Main Game Plugins

            // Right now, we're working on having the player sprite animated
            plugins::PlayerPlugin,

            // plugins::InteractionPlugin,
            // plugins::MobPlugin,
            plugins::TilemapPlugin
        ))
        .run();
}
