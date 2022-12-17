#include "Chunk.h"

void Chunk::Init(float posX, float posY, float posZ) {

	pos[0] = posX;
	pos[1] = posY;
	pos[2] = posZ;

	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			for (int k = 0; k < CHUNK_SIZE; k++) {

				ids[i][j][k] = (i + j + k) % 2;



			}
		}
	}

	for (int i = 1; i < CHUNK_SIZE-1; i++) {
		for (int j = 1; j < CHUNK_SIZE-1; j++) {
			for (int k = 1; k < CHUNK_SIZE-1; k++) {

				//what am i, if air stop.
				if (ids[i][j][k] == BLOCK_AIR) continue;

				//get 6 faces solid or not around me
				if (ids[i-1][j][k] == BLOCK_AIR) pushVertexes(i, j, k,-0.5f, 0.0f, 0.0f);
				if (ids[i+1][j][k] == BLOCK_AIR) pushVertexes(i, j, k,0.5f, 0.0f, 0.0f);
				if (ids[i][j-1][k] == BLOCK_AIR) pushVertexes(i, j, k,0.0f, -0.5f, 0.0f);
				if (ids[i][j+1][k] == BLOCK_AIR) pushVertexes(i, j, k,0.0f, 0.5f, 0.0f);
				if (ids[i][j][k-1] == BLOCK_AIR) pushVertexes(i, j, k,0.0f, 0.0f, -0.5f);
				if (ids[i][j][k+1] == BLOCK_AIR) pushVertexes(i, j, k,0.0f, 0.0f, 0.5f);




			}
		}
	}

	std::cout << "size of vertices: " << vertices.size() << ". size of indices: " << indices.size() << std::endl;
}

void Chunk::pushVertexes(int x, int y, int z, float xnorm, float ynorm, float znorm) {

	float xCoord = x + pos[0];
	float yCoord = y + pos[1];
	float zCoord = z + pos[2];


	int size = vertices.size();

	if (xnorm > 0) {
		//right
		BasicVertex v1{ {1.0f + xCoord, 0.0f + yCoord, 0.0f + zCoord}, {1.0f, 0.0f, 1.0f}, {1.0f, 1.0f} };
		BasicVertex v2{ {1.0f + xCoord, 0.0f + yCoord, 1.0f + zCoord}, {1.0f, 0.0f, 1.0f}, {0.0f, 1.0f} };
		BasicVertex v3{ {1.0f + xCoord, 1.0f + yCoord, 1.0f + zCoord}, {1.0f, 0.0f, 1.0f}, {0.0f, 0.0f} };
		BasicVertex v4{ {1.0f + xCoord, 1.0f + yCoord, 0.0f + zCoord}, {1.0f, 0.0f, 1.0f}, {1.0f, 0.0f} };

		vertices.push_back(v1);
		vertices.push_back(v2);
		vertices.push_back(v3);
		vertices.push_back(v4);
	}
	else if (xnorm < 0) {
		//left
		BasicVertex v1{ {0.0f + xCoord, 0.0f + yCoord, 1.0f + zCoord}, {0.0f, 1.0f, 1.0f}, {1.0f, 1.0f} };
		BasicVertex v2{ {0.0f + xCoord, 0.0f + yCoord, 0.0f + zCoord}, {0.0f, 1.0f, 1.0f}, {0.0f, 1.0f} };
		BasicVertex v3{ {0.0f + xCoord, 1.0f + yCoord, 0.0f + zCoord}, {0.0f, 1.0f, 1.0f}, {0.0f, 0.0f} };
		BasicVertex v4{ {0.0f + xCoord, 1.0f + yCoord, 1.0f + zCoord}, {0.0f, 1.0f, 1.0f}, {1.0f, 0.0f} };

		vertices.push_back(v1);
		vertices.push_back(v2);
		vertices.push_back(v3);
		vertices.push_back(v4);
	}
	else if (ynorm > 0) {
		//top
		BasicVertex v1{ {1.0f + xCoord, 1.0f + yCoord, 1.0f + zCoord}, {1.0f, 1.0f, 0.0f}, {1.0f, 1.0f} };
		BasicVertex v2{ {0.0f + xCoord, 1.0f + yCoord, 1.0f + zCoord}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f} };
		BasicVertex v3{ {0.0f + xCoord, 1.0f + yCoord, 0.0f + zCoord}, {1.0f, 1.0f, 0.0f}, {0.0f, 0.0f} };
		BasicVertex v4{ {1.0f + xCoord, 1.0f + yCoord, 0.0f + zCoord}, {1.0f, 1.0f, 0.0f}, {1.0f, 0.0f} };

		vertices.push_back(v1);
		vertices.push_back(v2);
		vertices.push_back(v3);
		vertices.push_back(v4);
	}
	else if (ynorm < 0) {
		//bottom
		BasicVertex v1{ {1.0f + xCoord, 0.0f + yCoord, 0.0f + zCoord}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f} };
		BasicVertex v2{ {0.0f + xCoord, 0.0f + yCoord, 0.0f + zCoord}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f} };
		BasicVertex v3{ {0.0f + xCoord, 0.0f + yCoord, 1.0f + zCoord}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f} };
		BasicVertex v4{ {1.0f + xCoord, 0.0f + yCoord, 1.0f + zCoord}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f} };

		vertices.push_back(v1);
		vertices.push_back(v2);
		vertices.push_back(v3);
		vertices.push_back(v4);
	}
	else if (znorm > 0) {
		//back
		BasicVertex v1{ {0.0f + xCoord, 0.0f + yCoord, 0.0f + zCoord}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f} };
		BasicVertex v2{ {1.0f + xCoord, 0.0f + yCoord, 0.0f + zCoord}, {1.0f, 0.0f, 0.0f},   {0.0f, 1.0f} };
		BasicVertex v3{ {1.0f + xCoord, 1.0f + yCoord, 0.0f + zCoord}, {1.0f, 0.0f, 0.0f},   {0.0f, 0.0f} };
		BasicVertex v4{ {0.0f + xCoord, 1.0f + yCoord, 0.0f + zCoord}, {1.0f, 0.0f, 0.0f},   {1.0f, 0.0f} };

		vertices.push_back(v1);
		vertices.push_back(v2);
		vertices.push_back(v3);
		vertices.push_back(v4);
	}
	else if (znorm < 0) {
		//front
		BasicVertex v1{ {1.0f + xCoord, 0.0f + yCoord, 1.0f + zCoord}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f} };
		BasicVertex v2{ {0.0f + xCoord, 0.0f + yCoord, 1.0f + zCoord}, {0.0f, 1.0f, 0.0f},   {0.0f, 1.0f} };
		BasicVertex v3{ {0.0f + xCoord, 1.0f + yCoord, 1.0f + zCoord}, {0.0f, 1.0f, 0.0f},   {0.0f, 0.0f} };
		BasicVertex v4{ {1.0f + xCoord, 1.0f + yCoord, 1.0f + zCoord}, {0.0f, 1.0f, 0.0f},   {1.0f, 0.0f} };

		vertices.push_back(v1);
		vertices.push_back(v2);
		vertices.push_back(v3);
		vertices.push_back(v4);
	}
	
	indices.push_back(size + 3);
	indices.push_back(size + 0);
	indices.push_back(size + 1);
	indices.push_back(size + 3);
	indices.push_back(size + 1);
	indices.push_back(size + 2);

}