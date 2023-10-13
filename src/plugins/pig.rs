// use bevy::prelude::*;
// use rand::Rng;
// use crate::plugins::*;
//
// pub struct PigPlugin;
//
// impl Plugin for PigPlugin {
//     fn build(&self, app: &mut App) {
//         app
//             .add_systems(Update, (spawn_pig, pig_lifetime, pig_move))
//             .register_type::<Pig>(); // This register type lets the debug menu see it ONLY after
//                                      // deriving default and reflect & reflecting the component
//     }
// }
//
//
// // Doing this allows us to edit the component's values with the debug menu
// #[derive(Component, Default, Reflect)]
// #[reflect(Component)]
// pub struct Pig {
//     pub lifetime: Timer,
//     pub movetime: Timer,
//     pub movedir: i32,
// }
//
//
// // This will spawn a pig
// pub fn spawn_pig(
//    mut commands: Commands,
//    asset_server: Res<AssetServer>,
//    input: Res<Input<KeyCode>>,
//    mut money: ResMut<Money>,
//    player: Query<&Transform, With<Player>>, 
// ) {
//     if !input.just_pressed(KeyCode::Space) {
//         return;
//     }
//
//     let player_transform = player.single();
//
//     if money.0 >= 10.0 {
//         money.0 -= 10.0;
//         info!("Spent $10.00, you now have ${}", money.0);
//
//         let texture = asset_server.load("pig.png");
//
//         commands.spawn((
//             SpriteBundle {
//                 texture,
//                 transform: Transform {
//                     translation: Vec3::new(
//                                      player_transform.translation.x + 15.0,
//                                      player_transform.translation.y + 15.0,
//                                      0.0
//                                      ),
//                     ..default()
//                 },
//                 ..default()
//             },
//             Pig {
//                 lifetime: Timer::from_seconds(10.0, TimerMode::Once),
//                 movetime: Timer::from_seconds(1.0, TimerMode::Once),
//                 movedir: 0,
//             },
//             Mob{
//                 target_delta_x: Vec3::new(player_transform.translation.x + 15.0, player_transform.translation.y, 0.0),
//                 target_delta_y: Vec3::new(player_transform.translation.x, player_transform.translation.y + 15.0, 0.0)
//             },
//             Name::new("Pig")
//         ));
//     }
// }
//
// pub fn pig_lifetime(
//     mut commands: Commands,
//     time: Res<Time>,
//     mut pigs: Query<(Entity, &mut Pig)>,
//     mut money: ResMut<Money>,
// ) {
//     for(pig_entity, mut pig) in &mut pigs {
//         pig.lifetime.tick(time.delta());
//
//         if pig.lifetime.finished() {
//             money.0 += 15.0;
//             commands.entity(pig_entity).despawn();
//
//             info!("Pig sold for $15.00, you now have ${}", money.0)
//         }
//     }
// }
//
// pub fn pig_move(
//     time: Res<Time>,
//     mut pigs: Query<(&mut Transform, &mut Pig, &mut Sprite, &mut Mob)>,
//     wall_query: Query<&Transform, (With<TileCollider>, Without<Mob>)>
// ) {
//     let mut rng = rand::thread_rng();
//     for (mut transform, mut pig, mut sprite, mut mob) in &mut pigs {
//         pig.movetime.tick(time.delta());
//         if pig.movetime.finished(){
//             pig.movedir = rng.gen_range(0..6);
//             let new_time = rng.gen_range(1.0..2.5);
//             pig.movetime = Timer::from_seconds(new_time, TimerMode::Once);
//         }
//         let move_amount = 100.0 * time.delta_seconds();
//         let mut delta_x = 0.0;
//         let mut delta_y = 0.0;
//         match pig.movedir { 
//             0 => return,
//             1 => delta_y -= move_amount,
//             2 => delta_y += move_amount,
//             3 => {
//                 delta_x -= move_amount;
//                 sprite.flip_x = true;
//             },
//             4 => {
//                 delta_x += move_amount;
//                 sprite.flip_x = false;
//             },
//             _ => {
//                 delta_x += move_amount;
//                 sprite.flip_x = false;
//             }
//         }
//         move_mob(&wall_query, &mut transform, &mut mob, delta_x, delta_y);
//     }
// }
