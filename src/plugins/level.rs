// use bevy::prelude::*;
// use rand::Rng;
//
// pub struct LevelPlugin;
//
// impl Plugin for LevelPlugin{
//     fn build(&self, app: &mut App) {
//         app
//             .add_systems(Startup, spawn_level);
//     }
// }
//
// // Component structs
// #[derive(Component)]
// pub struct Tile{}
//
// #[derive(Component)]
// pub struct Level {}
//
//
// // Systems 
//
// pub fn spawn_level(
//    mut commands: Commands,
//    asset_server: Res<AssetServer>,
// ) {
//     let texture_paths = ["ground.png", "wall.png"];
//     let mut rng = rand::thread_rng();
//
//     for x in 0..42{
//         for y in 0..42{
//             let index = rng.gen_range(0..2);
//             let texture = asset_server.load(texture_paths[index]);
//             commands.spawn((
//                 SpriteBundle{
//                     texture,
//                     transform: Transform {
//                         translation: Vec3::new( (x as f32)*16.00, (y as f32) * 16.00, -1.00 ),
//                         // translation: Vec3::new((x as f32)*16.00 - 800.00, (y as f32)*16.00 - 800.00, -1.00),
//                         ..default()
//                     },
//                     ..default()
//                 },
//                 Tile{},
//                 Name::new("Tile")
//             ));  
//         } 
//     }
// }
