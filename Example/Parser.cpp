#include "Parser.h"



CParser::CParser()
{
}


CParser::~CParser()
{
}

bool CParser::OpenFile(const char * Filename)
{
	Xfile.open(Filename, std::fstream::in);
	if (!Xfile.is_open())
	{
		return false;
	}
	return true;
}

void CParser::Parse(const char * Filename, std::vector<Mesh*>&MeshList)
{
	if (OpenFile(Filename))
	{
		std::getline(Xfile, Xline);
		if (!Xline.compare("xof 0303txt 0032"))
		{			
			Mesh* _Mesh;
			while (!Xfile.eof())
			{				
				std::getline(Xfile, Xline);
				int LineMesh = Xline.find("Mesh mesh");
				int LineNormals = Xline.find("MeshNormals normals");
				int LineTextCoords = Xline.find("MeshTextureCoords tc0");

				if (LineMesh != -1)
				{
					_Mesh = new Mesh;
					//Cantidad de vertices
					Xfile >> _Mesh->VertexSize >> ctemp;
					_Mesh->Vertices = new CVertex4[_Mesh->VertexSize];
					for (int i = 0; i < _Mesh->VertexSize; i++)
					{
						Xfile >> _Mesh->Vertices[i].x >> ctemp;

						Xfile >> _Mesh->Vertices[i].y >> ctemp;

						Xfile >> _Mesh->Vertices[i].z >> ctemp;

						Xfile >> ctemp;

					}
					//Cantidad de índices
					Xfile >> _Mesh->IndexSize >> ctemp;
					_Mesh->Indices = new unsigned short[_Mesh->IndexSize * 3];
					for (int i = 0; i < _Mesh->IndexSize * 3; i++)
					{
						Xfile >> ctemp >> ctemp >> _Mesh->Indices[i];
						i++;

						Xfile >> ctemp >> _Mesh->Indices[i];
						i++;

						Xfile >> ctemp >> _Mesh->Indices[i] >> ctemp >> ctemp;
					}
				}

				if (LineNormals != -1)
				{
					//Normales
					Xfile >> _Mesh->VertexSize >> ctemp;
					for (int i = 0; i < _Mesh->VertexSize; i++)
					{
						Xfile >> _Mesh->Vertices[i].nx >> ctemp;

						Xfile >> _Mesh->Vertices[i].ny >> ctemp;

						Xfile >> _Mesh->Vertices[i].nz >> ctemp;

						Xfile >> ctemp;
					}
				}

				if (LineTextCoords != -1)
				{
					//Coordenadas de textura
					Xfile >> _Mesh->VertexSize >> ctemp;
					for (int i = 0; i < _Mesh->VertexSize; i++)
					{
						Xfile >> _Mesh->Vertices[i].u >> ctemp;

						Xfile >> _Mesh->Vertices[i].v >> ctemp;
						Xfile >> ctemp;

					}
					MeshList.push_back(_Mesh);
				}
				//if (!Xline.compare(" Mesh mesh_pinata_cerdo_ {"))
				//{
				//	Xfile >> size >> ctemp;
				//	for (int i = 0; i < size; i++)
				//	{
				//		CVertex4 V;
				//		Xfile >> ftemp >> ctemp;
				//		V.x = ftemp;
				//		
				//		Xfile >> ftemp >> ctemp;
				//		V.y = ftemp;
				//		
				//		Xfile >> ftemp >> ctemp;
				//		V.z = ftemp;
				//		Xfile >> ctemp;
				//		Vertex.push_back(V);
				//		
				//	}
				//	Xfile >> size >> ctemp;
				//	for (int i = 0; i < size; i++)
				//	{
				//		Xfile >> ctemp >> ctemp >> stemp;
				//		Index.push_back(stemp);
				//		//Indices.push_back(stemp);
				//		Xfile >> ctemp >> stemp;
				//		Index.push_back(stemp);
				//		//Indices.push_back(stemp);
				//		Xfile >> ctemp >> stemp >> ctemp >> ctemp;
				//		Index.push_back(stemp);
				//		//Indices.push_back(stemp);
				//	}
				//}
				//if (!Xline.compare("  MeshNormals normals {"))
				//{
				//	Xfile >> size >> ctemp;
				//	if (size == Vertex.size())
				//	{
				//		for (int i = 0; i < Vertex.size(); i++)
				//		{
				//			Xfile >> ftemp >> ctemp;
				//			Vertex[i].nx = ftemp;
				//			Xfile >> ftemp >> ctemp;
				//			Vertex[i].ny = ftemp;
				//			Xfile >> ftemp >> ctemp;
				//			Vertex[i].nz = ftemp;
				//			Xfile >> ctemp;
				//		}
				//	}
				//}
				//if (!Xline.compare("  MeshTextureCoords tc0 {"))
				//{
				//	Xfile >> size >> ctemp;
				//	if (size == Vertex.size())
				//	{
				//		for (int i = 0; i < Vertex.size(); i++)
				//		{
				//			Xfile >> ftemp >> ctemp;
				//			Vertex[i].u = ftemp;
				//			Xfile >> ftemp >> ctemp;
				//			Vertex[i].v = ftemp;
				//			Xfile >> ctemp;
				//		}
				//	}
				//}
			}
		}
		Xfile.close();
	}
}