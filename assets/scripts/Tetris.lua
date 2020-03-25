Tetris = {
    assets = {
        [0] = { type="texture", id = "wallPiece", file = "../assets/sprites/Block.png" },
        [1] = { type="texture", id = "emptyBlock", file = "../assets/sprites/EmptyBlock.png" },
        [2] = { type="texture", id = "blueBlock", file = "../assets/sprites/BlueBlock.png" },
        [3] = { type="texture", id = "greenBlock", file = "../assets/sprites/GreenBlock.png" },
        [4] = { type="texture", id = "redBlock", file = "../assets/sprites/RedBlock.png" },
        [5] = { type="texture", id = "yellowBlock", file = "../assets/sprites/YellowBlock.png" },
        [6] = { type="texture", id = "purpleBlock", file = "../assets/sprites/PurpleBlock.png" },
        [7] = { type="texture", id = "whiteBlock", file = "../assets/sprites/WhiteBlock.png" },
        [8] = { type="texture", id = "brownBlock", file = "../assets/sprites/BrownBlock.png" },
        [9] = { type="texture", id = "blockBreakSpriteSheet", file = "../assets/spriteSheets/TetrisBlock.png" },
        [10] = { type="font", id = "charriot-font", file = "../assets/fonts/charriot.ttf", fontSize = 14 }
    },
    entities = {
        [0] = {
            name = "wallPiece",
            layer = 1,
            isActive = false,
            components = {
                [0] = {
                    type = "transform",
                    params = {
                        position = {
                            x = 100,
                            y = 100
                        },
                        scale = 1
                    }
                },
                [1] = {
                    type = "sprite",
                    params = {
                        textureAssetId = "wallPiece",
                        width = 32,
                        height = 32,
                        fixed = false
                    }
                }
            },
        },
        [1] = {
            name = "emptyBlock",
            layer = 1,
            isActive = false,
            components = {
                [0] = {
                    type = "transform",
                    params = {
                        position = {
                            x = 100,
                            y = 100
                        },
                        scale = 1
                    }
                },
                [1] = {
                    type = "sprite",
                    params = {
                        textureAssetId = "emptyBlock",
                        width = 32,
                        height = 32,
                        fixed = false
                    }
                }
            }
        },
        [2] = {
            name = "blueBlock",
            layer = 1,
            isActive = false,
            components = {
                [0] = {
                    type = "transform",
                    params = {
                        position = {
                            x = 100,
                            y = 100
                        },
                        scale = 1
                    }
                },
                [1] = {
                    type = "sprite",
                    params = {
                        textureAssetId = "whiteBlock",
                        width = 32,
                        height = 32,
                        fixed = false,
                         tint = {
                             r = 0,
                             g = 206,
                             b = 209
                         }
                    }
                }
            }
        },
        [3] = {
            name = "greenBlock",
            layer = 1,
            isActive = false,
            components = {
                [0] = {
                    type = "transform",
                    params = {
                        position = {
                            x = 100,
                            y = 100
                        },
                        scale = 1
                    }
                },
                [1] = {
                    type = "sprite",
                    params = {
                        textureAssetId = "whiteBlock",
                        width = 32,
                        height = 32,
                        fixed = false,
                        tint = {
                            r = 0,
                            g = 255,
                            b = 0
                        }
                    }
                }
            }
        },
        [4] = {
            name = "redBlock",
            layer = 1,
            isActive = false,
            components = {
                 [0] = {
                     type = "transform",
                     params = {
                         position = {
                             x = 100,
                             y = 100
                         },
                         scale = 1
                     }
                 },
                 [1] = {
                     type = "sprite",
                     params = {
                         textureAssetId = "whiteBlock",
                         width = 32,
                         height = 32,
                         fixed = false,
                         tint = {
                             r = 255,
                             g = 0,
                             b = 0
                         }
                     }
                 }
            }
        },
        [5] = {
            name = "yellowBlock",
            layer = 1,
            isActive = false,
            components = {
                 [0] = {
                     type = "transform",
                     params = {
                         position = {
                             x = 100,
                             y = 100
                         },
                         scale = 1
                     }
                 },
                 [1] = {
                     type = "sprite",
                     params = {
                         textureAssetId = "whiteBlock",
                         width = 32,
                         height = 32,
                         fixed = false,
                         tint = {
                             r = 255,
                             g = 255,
                             b = 0
                         }
                     }
                 }
            }
        },
        [6] = {
            name = "purpleBlock",
            layer = 1,
            isActive = false,
            components = {
                 [0] = {
                     type = "transform",
                     params = {
                         position = {
                             x = 100,
                             y = 100
                         },
                         scale = 1
                     }
                 },
                 [1] = {
                     type = "sprite",
                     params = {
                         textureAssetId = "whiteBlock",
                         width = 32,
                         height = 32,
                         fixed = false,
                         tint = {
                             r = 128,
                             g = 0,
                             b = 128
                         }
                     }
                 }
            }
        },
        [7] = {
            name = "whiteBlock",
            layer = 1,
            isActive = false,
            components = {
                 [0] = {
                     type = "transform",
                     params = {
                         position = {
                             x = 100,
                             y = 100
                         },
                         scale = 1
                     }
                 },
                 [1] = {
                     type = "sprite",
                     params = {
                         textureAssetId = "whiteBlock",
                         width = 32,
                         height = 32,
                         fixed = false
                     }
                 }
            }
        },
        [8] = {
            name = "brownBlock",
            layer = 1,
            isActive = false,
            components = {
                 [0] = {
                     type = "transform",
                     params = {
                         position = {
                             x = 100,
                             y = 100
                         },
                         scale = 1
                     }
                 },
                 [1] = {
                     type = "sprite",
                     params = {
                         textureAssetId = "whiteBlock",
                         width = 32,
                         height = 32,
                         fixed = false,
                         tint = {
                             r = 129,
                             g = 69,
                             b = 19
                         }
                     }
                 }
            }
        },
        [9] = {
            name = "breakAnimation",
            layer = 2,
            isActive = true,
            components = {
                 [0] = {
                      type = "transform",
                      params = {
                          position = {
                              x = 100,
                              y = 100
                          },
                          scale = 1
                      }
                 },
                 [1] = {
                     type = "sprite",
                     params = {
                         textureAssetId = "blockBreakSpriteSheet",
                         width = 32,
                         height = 32,
                         fixed = false
                     }
                 },
                 [2] = {
                     type = "spriteAnimation",
                     params = {
                         spriteSheetInfoFile = "../assets/spriteSheets/TetrisBlock.json",
                         animationSpeed = 1.5
                     }
                 }
             }
         }
    }
}