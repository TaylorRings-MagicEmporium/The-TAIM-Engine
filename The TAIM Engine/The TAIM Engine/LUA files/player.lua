EntityList = {		
	duck = {
		Transform = {
			Position = {
				x = 0,
				y = 3,
				z = 0
			},
			Rotation = {
				degrees = 90.0,
				axisX = 0.5,
				axisY = 0.5,
				axisZ = 0
			},
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
		--CubeCollider = {
		--	sizeX = 1,
		--	sizeY = 1,
		--	sizeZ = 1
		--},
		SphereCollider = {
			radius = 1.0
		},
		AudioPlayer = {
			AudioPath = "gun-shot.wav"
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
				axisX = 0,
				axisY = 0,
				axisZ = 1.0
			}
		},
		MeshRenderer = {
			MeshPath = "Objects/Prim/cube.obj",
			ShaderName = "model_loading",
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
	}
}