use bevy::prelude::*;
use crate::plugins::*;

#[test]
fn test_conversion_small_pos() {
    let test_pos1 = Vec2::new(18.002, 8.00);
    assert_eq!(mouse_to_grid_pos(test_pos1), Vec2::new(16.0, 0.0));
}

#[test]
fn test_conversion_small_neg() {
    let test_pos2 = Vec2::new(-2.0, 54.3);
    assert_eq!(mouse_to_grid_pos(test_pos2), Vec2::new(0.0, 48.0));

}

