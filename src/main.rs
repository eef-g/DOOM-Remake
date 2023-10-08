use bevy::prelude::*;

mod systems;
mod components;
mod resources;

use crate::systems as gs;
use crate::resources as gr;


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
        .insert_resource(gr::Money(100.0))
        .add_systems(Startup, (gs::spawn_level, gs::setup))
        .add_systems(Update, 
            (
                // Player systems
                gs::character_movement,
                // Pig systems
                gs::spawn_pig, gs::pig_lifetime, gs::pig_move
            ))
        .run();
}
