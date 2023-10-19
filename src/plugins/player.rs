use bevy::{prelude::*, render::camera::ScalingMode};
use bevy_rapier2d::prelude::*;

pub struct PlayerPlugin;

impl Plugin for PlayerPlugin{
    fn build(&self, app: &mut App) {
        app
            .add_systems(Startup, spawn_player)
            .add_systems(Update, (
                player_movement,
                animate_sprite,
            ))
            .insert_resource(Money(100.0));
    }
}

// Components
#[derive(Component)]
pub struct Player {
    pub speed: f32,
}

#[derive(Component)]
pub struct AnimationIndicies {
    pub first: usize,
    pub last: usize
}

#[derive(Component)]
pub struct AnimationTimer(Timer);


// Resources
#[derive(Resource)]
pub struct Money(pub f32);

#[derive(Resource)]
pub struct PlayerStatus(pub PlayerState);


// Systems
//
pub enum PlayerState {
    WALK,
    CARRY,
    IDLE,
    WATERING,
    HIT,
    DEATH,
    DOING,
    RUNNING,
    JUMPING,
    ROLLING,
    AXE,
    PICKAXE,
    SWIMMING,
    HAMMER,
    SWORD,
    CASTING,
    WAITING,
    CAUGHT,
    REELING,
    SHOVEL
}

pub fn spawn_player(
    mut commands: Commands,
    asset_server: Res<AssetServer>,
    mut texture_atlases: ResMut<Assets<TextureAtlas>>
) {
    // Spawn a camera that lets us actually treat this like a game
    let mut main_camera = Camera2dBundle::default();
    let default_width = 256.00;
    let default_height = 144.00;
    main_camera.projection.scaling_mode = ScalingMode::AutoMin{ 
        min_width: default_width * 2.5,
        min_height: default_height * 2.5
    };

    // Set up the player sprite sheets (For now, it's just the idle animation)
    let texture_handle = asset_server.load("character_sheet.png");
    let texture_atlas = 
        TextureAtlas::from_grid(texture_handle, Vec2::new(64.0, 64.0), 23, 20, None, None);
    let texture_atlas_handle = texture_atlases.add(texture_atlas);
    let animation_indicies = AnimationIndicies { first: 0, last: 5};

    // Set the starting position of the player (Later, we'll read a save file)
    let pos_x = Vec3::new(100.0, 0.0, 0.5);
    let pos_y = Vec3::new(0.0, 50.0, 0.5);
    // Now spawn a SpriteBundle -- This is a collection of components that let us use a sprite
    commands.spawn(( // We have 2 parenthesis here since if we want multiple components then we
        // pass in a tuple of the components to the spawn function
        RigidBody::KinematicPositionBased,
        Collider::capsule(Vec2::new(0.0, 0.0), Vec2::new(0.0, 2.0), 5.0),
        KinematicCharacterController::default(),
        SpriteSheetBundle {
            texture_atlas: texture_atlas_handle,
            sprite: TextureAtlasSprite::new(animation_indicies.first),
            transform: Transform { 
                translation: pos_x + pos_y,
                ..default()
            },
            ..default()
        },
        animation_indicies,
        AnimationTimer(Timer::from_seconds(0.2, TimerMode::Repeating)),
        Player{
            speed: 100.0,
        },
        Name::new("Player")
    ))
    // Add the camera as a child so that way it automatically follows the player
    .with_children(|parent| {
        parent.spawn(main_camera);
    });
}


pub fn animate_sprite(
    time: Res<Time>,
    mut query: Query<(
        &AnimationIndicies,
        &mut AnimationTimer,
        &mut TextureAtlasSprite,
    )>
) {
    for (indicies, mut timer, mut sprite) in &mut query {
        timer.0.tick(time.delta());
        if timer.0.just_finished() {
            sprite.index = if sprite.index == indicies.last {
                indicies.first
            } else {
                sprite.index + 1
            };
        }
    }
}

pub fn player_movement(
    mut controllers: Query<( &mut KinematicCharacterController, &mut TextureAtlasSprite, &Player)>,
    time: Res<Time>,
    input: Res<Input<KeyCode>>
) {
    for (mut controller, mut sprite, player) in controllers.iter_mut() {
        let move_amount =  player.speed * time.delta_seconds();
        let mut delta_x = 0.0;
        let mut delta_y = 0.0;

        if input.pressed(KeyCode::W) {
            delta_y += move_amount;
        }
        if input.pressed(KeyCode::S) {
            delta_y -= move_amount;
        }
        if input.pressed(KeyCode::D) {
            delta_x += move_amount;
            sprite.flip_x = false;
            
        }
        if input.pressed(KeyCode::A) {
            delta_x -= move_amount;
            sprite.flip_x = true;
        }
        controller.translation = Some(Vec2::new(delta_x, delta_y));
    }

}

pub fn animation_swap(
    status: ResMut<PlayerStatus>
) {
    // Use serde to read the JSON file and get the correct response
}
