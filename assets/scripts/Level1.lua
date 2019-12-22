Level1 = {
    assets = {
        [0] = { type="texture", id = "terrain-texture-day", file = "../assets/tilemaps/jungle.png" },
        [1] = { type="texture", id = "terrain-texture-night", file = "../assets/tilemaps/jungle-night.png" },
        [2] = { type="texture", id = "chopper-texture", file = "../assets/images/chopper-spritesheet.png" },
        [3] = { type="texture", id = "tank-texture-big-left", file = "../assets/images/tank-big-left.png" },
        [4] = { type="texture", id = "projectile-texture", file = "../assets/images/bullet-enemy.png" },
        [5] = { type="font", id = "charriot-font", file = "../assets/fonts/charriot.ttf", fontSize = 14 },
        [6] = { type="texture", id = "start-texture", file = "../assets/images/start.png" },
        [7] = { type="texture", id = "tank-big-right-texture", file = "../assets/images/tank-big-right.png" },
        [8] = { type="texture", id = "projectile-texture", file = "../assets/images/bullet-enemy.png" }
    },
    map = {
        textureAssetId = "terrain-texture-night",
        file = "../assets/tilemaps/jungle.map",
        scale = 2,
        tileSize = 32,
        mapSizeX = 25,
        mapSizeY = 20
    },
    entities = {
        [0] = {
            name = "player",
            layer = 4,
            components = {
                [0] = {
                    type = "transform",
                    params = {
                        position = {
                            x = 240,
                            y = 115
                        },
                        scale = 1
                    }
                },
                [1] = {
                    type = "sprite",
                    params = {
                        textureAssetId = "chopper-texture",
                        width = 32,
                        height = 32,
                        fixed = false
                    }
                },
                [2] = {
                    type = "spriteAnimation",
                    params = {
                        totalFrames = 2,
                        animationSpeed = 90,
                        isDirectional = true
                    }
                },
                [3] = {
                    type = "boxCollider",
                    params = {
                        tag = "PLAYER",
                        offsetX = 0,
                        offsetY = 0,
                        width = 32,
                        height = 32
                    }
                }
            }
        },
        [1] = {
            name = "start",
            layer = 3,
            components = {
                [0] = {
                    type = "transform",
                    params = {
                        position = {
                            x = 240,
                            y = 115
                        },
                        scale = 1,
                        rotation = 0
                    }
                },
                [1] = {
                    type = "sprite",
                    params = {
                        textureAssetId = "start-texture",
                        width = 32,
                        height = 32,
                        fixed = false
                    }
                }
            }
        },
        [2] = {
            name = "tank1",
            layer = 2,
            components = {
                [0] = {
                    type = "transform",
                    params = {
                        position = {
                            x = 150,
                            y = 500;
                        },
                        scale = 1
                    }
                },
                [1] = {
                    type = "sprite",
                    params = {
                        textureAssetId = "tank-big-right-texture",
                        width = 32,
                        height = 32
                    }
                },
                [2] = {
                    type = "boxCollider",
                    params = {
                        tag = "ENEMY",
                        width = 32,
                        height = 32
                    }
                }
            }
        },
        [3] = {
            name = "projectile",
            layer = 3,
            components = {
                [0] = {
                    type = "transform",
                    params = {
                        position = {
                            x = 175,
                            y = 508;
                        },
                        scale = 0.25
                    }
                },
                [1] = {
                    type = "sprite",
                    params = {
                        textureAssetId = "projectile-texture",
                        width = 32,
                        height = 32
                    }
                },
                [2] = {
                    type = "boxCollider",
                    params = {
                        tag = "PROJECTILE",
                        width = 32,
                        height = 32
                    }
                },
                [3] = {
                    type = "projectile",
                    params = {
                        speed = 50,
                        angle = 0,
                        range = 100,
                        loop = true
                    }
                }
            }
        }
    }
}
