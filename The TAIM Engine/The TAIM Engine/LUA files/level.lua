EntityList = {
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
	StatCamera = {
		Transform = {
			Position = {
				x = 0,
				y = 10,
				z = 20
			},
			Tag = "SceneCamera"
		},
		Camera = {
			Type = "STATIC",
			Target = {
				x = 0,
				y = 0,
				z = 9
			}
		}	
	},
	target1 = {
		Transform = {
			Position = {
				x = 5.0,
				y = 0.5,
				z = -5.0
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
		},
		Animator = {
			Type = "Bubble_shrink",
			loop = false,
			start = false
		}
	},
	target2 = {
		Transform = {
			Position = {
				x = 0.0,
				y = 0.5,
				z = -5.0
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
		},
		Animator = {
			Type = "Bubble_shrink",
			loop = false,
			start = false
		}
	},
	target3 = {
		Transform = {
			Position = {
				x = -5.0,
				y = 0.5,
				z = -5.0
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
		},
		Animator = {
			Type = "Bubble_shrink",
			loop = false,
			start = false
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
	}
}