EntityList = {		
	duck = {
		Transform = {
			Position = {
				x = 0,
				y = 3,
				z = 0
			},
			--Rotation = {
			--	degrees = 90.0,
			--	axisX = 0.5,
			--	axisY = 0.5,
			--	axisZ = 0
			--},
			Tag = "Player"
		},
		MeshRenderer = {
			MeshPath = "Objects/duck/duck.obj",
			ShaderName = "model_loading",
			flipImage = false
		},
		Rigidbody = {
			offset = {
				x = 0,
				y = 0,
				z = 0
			},
			mass = 1.0,
			LockX = true,
			LockZ = true
		},
		SphereCollider = {
			radius = 1.0
		},
		AudioPlayer = {
			AudioPath = "gun-shot.wav"
		},
		Camera = {
			Type = "FIRST",
			Offset = {
				x = 0,
				y = 1,
				z = -1
			}
		}
	},
	ground = {
		Transform = {
			Position = {
				x = 0,
				y = -3,
				z = 0
			},
			Scale = {
				x = 10,
				y = 1,
				z = 10
			}
		},
		MeshRenderer = {
			MeshPath = "Objects/Prim/cube.obj",
			ShaderName = "basic",
			flipImage = false
		},
		Rigidbody = {
			offset = {
				x = 0,
				y = 0,
				z = 0
			},
			mass = 0.0
		},
		CubeCollider = {
			sizeX = 10,
			sizeY = 1,
			sizeZ = 10
		}
	},
	pie = {
		Transform = {
			Position = {
			x = 3,
			y = 0,
			z = 0
			}
		},
	
		MeshRenderer = {
			MeshPath = "Objects/duck/duck.obj",
			ShaderName = "model_loading",
			flipImage = false
		}
	},
	ground2 = {
		Transform = {
			Position = {
				x = 0,
				y = -3,
				z = -10
			},
			Scale = {
				x = 10,
				y = 1,
				z = 10
			},
			Rotation = {
				degrees = 90.0,
				axisX = 1.0,
				axisY = 0,
				axisZ = 0
			}
		},
		MeshRenderer = {
			MeshPath = "Objects/Prim/cube.obj",
			ShaderName = "basic",
			Colour = {
				r = 1.0,
				g = 1.0,
				b = 0.5,
				a = 1.0
			},
			flipImage = false
		},
		Rigidbody = {
			offset = {
				x = 0,
				y = 0,
				z = 0
			},
			mass = 0.0
		},
		CubeCollider = {
			sizeX = 10,
			sizeY = 1,
			sizeZ = 10
		}
	},
	ghost = {
		Transform = {
			Position = {
			x = 1,
			y = 1,
			z = 1
			},
			Tag = "Ghost"
		},
		MeshRenderer = {
			MeshPath = "Objects/ghost duck/duck.obj",
			ShaderName = "model_loading",
			flipImage = false
		}
	},
	target = {
		Transform = {
			Position = {
				x = 5.0,
				y = 0.5,
				z = 5.0
			},
			Tag = "Target"
		},
		MeshRenderer = {
			MeshPath = "Objects/target/target.obj",
			ShaderName = "model_loading",
			flipImage = false
		},
		CubeCollider = {
			sizeX = 1,
			sizeY = 1,
			sizeZ = 0.5
		},
		Rigidbody = {
			offset = {
				x = 0,
				y = 0,
				z = 0
			},
			mass = 0.0
		}
	},
	StatCamera = {
		Transform = {
			Position = {
				x = 0,
				y = 10,
				z = 20
			},
			Tag = "SceneCamera"
		}
		--Camera = {
		--	Type = "STATIC",
		--	Target = {
		--		x = 0,
		--		y = 0,
		--		z = 9
		--	}
		--}	
	}
}