use bevy::prelude::*;
use crate::components as gc;
use rand::Rng;


pub fn spawn_level(
   mut commands: Commands,
   asset_server: Res<AssetServer>,
) {
    let texture_paths = ["ground.png", "wall.png"];
    let mut rng = rand::thread_rng();

    for x in 0..100{
        for y in 0..100{
            let index = rng.gen_range(0..2);
            let texture = asset_server.load(texture_paths[index]);
            commands.spawn((
                SpriteBundle{
                    texture,
                    transform: Transform { 
                        translation: Vec3::new((x as f32)*16.00 - 800.00, (y as f32)*16.00 - 800.00, -1.00),
                        ..default()
                    },
                    ..default()
                },
                gc::Tile{}
            ));  
        } 
    }
}
