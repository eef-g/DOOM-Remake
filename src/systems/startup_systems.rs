use bevy::prelude::*;
use crate::components as c;


pub fn setup(mut commands: Commands, asset_server: Res<AssetServer>) {
    // Spawn a camera that lets us actually treat this like a game
    commands.spawn(Camera2dBundle::default());

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
    ));
}
