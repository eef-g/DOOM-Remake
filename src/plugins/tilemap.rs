use bevy::prelude::*;
use bevy_rapier2d::prelude::*;
use std::fs::File;
use std::io::*;
use rand::Rng;

pub struct TilemapPlugin;

impl Plugin for TilemapPlugin {
    fn build(&self, app: &mut App) {
        app
         .add_systems(Startup, create_simple_map);
    }
}


// Components
#[derive(Component)]
pub struct Tile{
    pub tile_type: TileType
}

pub enum TileType {
    GROUND,
    STONE,
    BEDROCK
}

// Systems 
fn create_simple_map(
    mut commands: Commands,
    asset_server: Res<AssetServer>
) {
    let _ = generate_map(15);
    let file = File::open("assets/saves/generated.txt").expect("No map file found");
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

fn generate_map(size: i32) -> Result<()> {
    let path = "assets/saves/generated.txt".to_string();
    let mut world_string = "".to_string();
    let mut rng = rand::thread_rng();
    for x in 0..size{
        for y in 0..size {
            // info!("Generating tile [{},{}]", x, y);
            if x == 0 || x == size-1 || y == 0 || y == size-1 {
                world_string += "b";
            } else {
                let wall = rng.gen_bool(0.3);
                if wall {
                    world_string += "#";
                } else {
                    world_string += ".";
                }
            }
        }
        world_string += "\n";
    }
    let mut output = File::create(path)?;
    write!(output, "{}", world_string)?;

    Ok(())
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
    )).id();

    // Run through different tile types and assign proper values
    match ch {
        // Stone
        '#' => {
            commands.entity(tile).insert(Tile{tile_type: TileType::STONE});
            commands.entity(tile).insert(Collider::cuboid(8.0, 8.0));
        },
        // Bedrock
        'b' => {
            commands.entity(tile).insert(Tile{tile_type: TileType::BEDROCK});
            commands.entity(tile).insert(Collider::cuboid(8.0, 8.0));
        },
        // Ground
        '.' => {
            commands.entity(tile).insert(Tile{tile_type: TileType::GROUND});
        }
        // Default
        _ => {
            commands.entity(tile).insert(Tile{tile_type: TileType::GROUND});
        }
    }

    // Final tile prep
    let tile_name = format!("[{}, {}]", x, y);
    commands.entity(tile).insert(Name::new(tile_name));
    return tile;
}
