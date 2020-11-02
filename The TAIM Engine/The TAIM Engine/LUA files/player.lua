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
			mass = 1.0
		},
		Collider = {
			sizeX = 1,
			sizeY = 1,
			sizeZ = 1
		}
	},
	ground = {
		Transform = {
			Position = {
				x = 0,
				y = -3,
				z = 0
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
		Collider = {
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
	}
}