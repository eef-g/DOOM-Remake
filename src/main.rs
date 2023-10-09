use bevy::prelude::*;

mod plugins;

fn main() {
    App::new()
        // Making ImagePlugin to default_nearest allows sprites to keep their resolution
        .add_plugins(DefaultPlugins
            .set(ImagePlugin::default_nearest())
            .set(WindowPlugin {
                primary_window: Some(Window {
                    title: "The Caverns".into(),
                    resolution: (640.0, 480.0).into(),
                    resizable: false,
                    ..default()
                }),
                ..default()
            })
            .build(),
        )
        .add_plugins((
                // Debug plugin goes first -- comment out if not wanting to debug
                plugins::DebugPlugin,
                plugins::PlayerPlugin, 
                plugins::PigPlugin 
                // Commenting out the level plugin for now
                //plugins::LevelPlugin
        ))
        .run();
}
