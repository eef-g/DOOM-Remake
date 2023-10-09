use bevy::prelude::*;
use std::fs::File;
use std::io::*;

pub struct TilemapPlugin;

impl Plugin for TilemapPlugin {
    fn build(&self, app: &mut App) {
        app
         .add_systems(Startup, create_simple_map);
    }
}


// Components
#[derive(Component)]
pub struct Tile{}

#[derive(Component)]
pub struct TileCollider{}



// Systems 
fn create_simple_map(
    mut commands: Commands,
    asset_server: Res<AssetServer>
) {
    let file = File::open("assets/map.txt").expect("No map file found");
    let tile_size = 16;
    let mut map = Vec::new();

    for (y, line) in BufReader::new(file).lines().enumerate() {
        if let Ok(line) = line {
            for(x, ch) in line.chars().enumerate() {
                let tile = spawn_ascii_tile(
                    &mut commands, 
                    &asset_server, 
                    ch, 
                    x as i32, 
                    y as i32, 
                    tile_size
                );
                map.push(tile);
            }
        }
    }

    commands.spawn((
            Transform::default(),
            GlobalTransform::default(),
            VisibilityBundle::default(),
        ))
        .insert(Name::new("Map"))
        .push_children(&map);
}

fn decode_from_ascii(ch: char) -> String {
    match ch {
        '.' => return "ground.png".to_string(),
        '#' => return "wall.png".to_string(),
        _ => return "wall.png".to_string()
    }
}

fn spawn_ascii_tile(commands: &mut Commands, asset_server: &Res<AssetServer>, ch: char, x: i32, y: i32, size: i32) -> Entity {
    let texture = asset_server.load(decode_from_ascii(ch));
    let tile = commands.spawn((
        SpriteBundle {
            texture,
            transform: Transform { 
                translation: Vec3::new( (x * size) as f32,  (y * size) as f32, -1.0),
                ..default()
            },
            ..default()
        },
        Tile{},
    )).id();

    if ch == '#' { 
        commands.entity(tile).insert(TileCollider{});
        commands.entity(tile).insert(Name::new("Wall Tile"));
    }
    else {
        commands.entity(tile).insert(Name::new("Tile"));
    }
    return tile;
}
