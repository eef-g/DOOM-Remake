use bevy::{prelude::*, render::camera::ScalingMode, sprite::collide_aabb::collide};

use super::TileCollider;
use crate::plugins::*;

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
            transform: Transform {
                translation: Vec3::new(50.0, 50.0, 1.0),
                ..default()
            },
            ..default()
        },
        Player{
            speed: 100.0,
        },
        Mob{
            is_colliding: false,
            target_delta_x: Vec3::splat(0.0),
            target_delta_y: Vec3::splat(0.0)
        },
        Name::new("Player")
    ))
    // Add the camera as a child so that way it automatically follows the player
    .with_children(|parent| {
        parent.spawn(main_camera);
    });
}

pub fn player_movement(
    mut characters: Query<(&mut Transform, &Player, &mut Sprite, &mut Mob)>,
    input: Res<Input<KeyCode>>,
    time: Res<Time>,
) {
    for (mut transform, player, mut sprite, mut mob) in &mut characters {
        let move_amount = player.speed * time.delta_seconds();
        let mut x_delta = 0.0;
        let mut y_delta = 0.0;

        if input.pressed(KeyCode::W) {
            y_delta += move_amount;
        }
        if input.pressed(KeyCode::S) {
            y_delta -= move_amount;
        }
        if input.pressed(KeyCode::D) {
            x_delta += move_amount;
            sprite.flip_x = false;
            
        }
        if input.pressed(KeyCode::A) {
            x_delta -= move_amount;
            sprite.flip_x = true;
        }
        mob.target_delta_x = Vec3::new(x_delta, 0.0, 0.0);
        mob.target_delta_y = Vec3::new(0.0, y_delta, 0.0);
        let target = mob.target_delta_x + mob.target_delta_y;
        if !mob.is_colliding {
            transform.translation = target;
        }
    }
}
