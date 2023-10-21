use bevy::prelude::*;
use bevy_ecs_tilemap::prelude::*;
use bevy_rapier2d::prelude::*;

pub struct MapPlugin;

impl Plugin for MapPlugin {
    fn build(&self, app: &mut App) {
        app
            .add_plugins(TilemapPlugin)
            .add_systems(Startup, create_simple_map)
            .insert_resource(ClearColor(Color::hex("#0099db").unwrap()));
    }
}

fn create_simple_map(
    mut commands: Commands,
    asset_server: Res<AssetServer>,
) {

    // Initialize the size of the map
    let map_size = TilemapSize { x: 32, y: 32};

    // Initialize the tilemap texture
    let texture_handle: Handle<Image> = asset_server.load("tilemap.png");
    
    // Create a tilemap entity early
    let tilemap_entity = commands.spawn_empty().id();

    // Now create the tilemap storage component
    let mut tile_storage = TileStorage::empty(map_size);

    // Spawn the elements of the tilemap
    for x in 0..map_size.x {
        for y in 0..map_size.y {
            let tile_pos = TilePos { x, y };
            let tile_name = format!("[{}, {}]", tile_pos.x, tile_pos.y); 
            let tile_entity = commands
                .spawn(TileBundle {
                    position: tile_pos,
                    tilemap_id: TilemapId(tilemap_entity),
                    texture_index: TileTextureIndex(0),
                    ..Default::default()
                })
                .insert(Name::new(tile_name))
                .id();
            // Add the tile to the tilemap storage
            tile_storage.set(&tile_pos, tile_entity);
        }
    }
    // Set the tile size to be 16px by 16px
    let tile_size = TilemapTileSize { x: 16.0, y: 16.0 };
    let grid_size: TilemapGridSize = tile_size.into();
    let map_type = TilemapType::Square;

    commands.entity(tilemap_entity).insert(TilemapBundle {
        grid_size,
        map_type,
        size: map_size,
        storage: tile_storage,
        texture: TilemapTexture::Single(texture_handle),
        tile_size,
        visibility: Visibility::Visible,
        transform: get_tilemap_center_transform(&map_size, &grid_size, &map_type, 0.5),
        ..Default::default()
    });

    // Once the tilemap is made, we want to add the colliders to the tiles that are on the edge
}
