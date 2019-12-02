window = {
    title = "301 GameEngine",
    width = 800,
    height = 600
}

directories = {
	textures = "Textures/",
	sprites = "../Sprites/",
	audiofiles = "../AudioFiles/"
}


environment= {
	filename = "environment.obj",
	texture = "sand.bmp",
	position = {
		 X = 0, 
		 Y = 0, 
		 Z = 0
	},
	scale = {
		 X = 1000,
		 Y = 1000,
		 Z = 1000
	},
	rotate = 0, 
	rotateVec = {
		 X = 0,
		 Y = 1,
		 Z = 0
	},
	objectToFollow = false
}

mustang={
	filename = "mustang.obj",
	texture = "asphalt.bmp",
	position = {
		X = 0,
		Y = 40,
		Z = 0
	},
	scale = {
		X = 3,
		Y = 3, 
		Z = 3
	},
	rotate = 0,
	rotateVec = {
		X = 0,
		Y = 1, 
		Z = 0
	},
	objectToFollow = true
}