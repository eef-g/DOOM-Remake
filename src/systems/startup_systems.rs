use bevy::{prelude::*, render::camera::ScalingMode};
use crate::components as c;


pub fn setup(mut commands: Commands, asset_server: Res<AssetServer>) {
    

    // Spawn a camera that lets us actually treat this like a game
    let mut main_camera = Camera2dBundle::default();

    let default_width = 256.00;
    let default_height = 144.00;
    main_camera.projection.scaling_mode = ScalingMode::AutoMin{ 
        min_width: default_width * 2.0,
        min_height: default_height * 2.0
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
        c::Player{
            speed: 100.0,
        }
    ))
    // Add the camera as a child so that way it automatically follows the player
    .with_children(|parent| {
        parent.spawn(main_camera);
    });
}
