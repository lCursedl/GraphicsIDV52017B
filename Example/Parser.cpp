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
				int LineMaterials = Xline.find("MeshMaterialList mtls");
				float * TempVec;
				float * TempNrml;
				float * TempTxt;

				if (LineMesh != -1)
				{
					_Mesh = new Mesh;
					//Cantidad de vertices
					Xfile >> _Mesh->VertexSize >> ctemp;
					/*_Mesh->Vertices = new CVertex4[_Mesh->VertexSize];
					for (int i = 0; i < _Mesh->VertexSize; i++)
					{
						Xfile >> _Mesh->Vertices[i].x >> ctemp;

						Xfile >> _Mesh->Vertices[i].y >> ctemp;

						Xfile >> _Mesh->Vertices[i].z >> ctemp;

						Xfile >> ctemp;

					}*/
					//Dinamic vertex
					TempVec = new float[_Mesh->VertexSize * (_Mesh->Stride / 4)];
					_Mesh->Vertex = new float[_Mesh->VertexSize * (_Mesh->Stride / 4)];
					for (long i = 0; i < _Mesh->VertexSize * 4; i++)
					{
						Xfile >> TempVec[i] >> ctemp;
						std::cout << TempVec[i] << std::endl;
						i++;
						
						Xfile >> TempVec[i] >> ctemp;
						std::cout << TempVec[i] << std::endl;
						i++;

						Xfile >> TempVec[i] >> ctemp >> ctemp;
						std::cout << TempVec[i] << std::endl;
						i++;

						TempVec[i] = 1.0f;
						std::cout << TempVec[i] << std::endl;
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

				//if (LineNormals != -1)
				//{
				//	_Mesh->Stride += 16;
				//	TempNrml = new float[_Mesh->VertexSize * 4];
				//	//Normales
				//	Xfile >> _Mesh->VertexSize >> ctemp;
				//	/*for (int i = 0; i < _Mesh->VertexSize; i++)
				//	{
				//		Xfile >> _Mesh->Vertices[i].nx >> ctemp;

				//		Xfile >> _Mesh->Vertices[i].ny >> ctemp;

				//		Xfile >> _Mesh->Vertices[i].nz >> ctemp; 

				//		Xfile >> ctemp;
				//	}*/
				//	//Dinamic normals
				//	for (int i = 0; i < _Mesh->VertexSize * 4; i++)
				//	{
				//		//NX
				//		Xfile >> TempNrml[i] >> ctemp;
				//		i++;
				//		//NY
				//		Xfile >> TempNrml[i] >> ctemp;
				//		i++;
				//		//NZ
				//		Xfile >> TempNrml[i] >> ctemp;
				//		Xfile >> ctemp;
				//		i++;
				//		//NW
				//		TempNrml[i] = 1.0f;
				//	}
				//}

				//if (LineTextCoords != -1)
				//{
				//	//Coordenadas de textura
				//	/*Xfile >> _Mesh->VertexSize >> ctemp;
				//	for (int i = 0; i < _Mesh->VertexSize; i++)
				//	{
				//		Xfile >> _Mesh->Vertices[i].u >> ctemp;

				//		Xfile >> _Mesh->Vertices[i].v >> ctemp;
				//		Xfile >> ctemp;

				//	}*/
				//	//Dinamic Texcoords
				//	_Mesh->Stride += 8;
				//	float * TempT = new float[_Mesh->VertexSize * (_Mesh->Stride / 4)];
				//	int offsetpos = 0;					

				//	for (int i = 0; i < _Mesh->VertexSize * (_Mesh->Stride / 4); i++)
				//	{
				//		if (_Mesh->HasNormal)
				//		{
				//			for (offsetpos; offsetpos < _Mesh->VertexSize * ((_Mesh->Stride - 8) * 4); offsetpos++)
				//			{
				//				//X
				//				TempT[i] = _Mesh->Vertex[offsetpos];
				//				i++;
				//				offsetpos++;
				//				//Y
				//				TempT[i] = _Mesh->Vertex[offsetpos];
				//				i++;
				//				offsetpos++;
				//				//Z
				//				TempT[i] = _Mesh->Vertex[offsetpos];
				//				i++;
				//				offsetpos++;
				//				//W
				//				TempT[i] = _Mesh->Vertex[offsetpos];
				//				i++;
				//				offsetpos++;
				//				//NX
				//				TempT[i] = _Mesh->Vertex[offsetpos];
				//				i++;
				//				offsetpos++;
				//				//NY
				//				TempT[i] = _Mesh->Vertex[offsetpos];
				//				i++;
				//				offsetpos++;
				//				//NZ
				//				TempT[i] = _Mesh->Vertex[offsetpos];
				//				i++;
				//				offsetpos++;
				//				//NW
				//				TempT[i] = _Mesh->Vertex[offsetpos];
				//				i++;
				//				//U
				//				Xfile >> _Mesh->Vertex[i] >> ctemp;
				//				i++;
				//				//V
				//				Xfile >> _Mesh->Vertex[i] >> ctemp >> ctemp;								
				//			}
				//		}
				//		else
				//		{
				//			
				//		}						
				//	}
				//	delete[] _Mesh->Vertex;
				//	_Mesh->Vertex = new float[_Mesh->VertexSize * (_Mesh->Stride / 4)];
				//	_Mesh->Vertex = TempT;
				//	delete[] TempT;
				//	MeshList.push_back(_Mesh);
				//}

				if (LineMaterials != -1)
				{
					Xfile >> _Mesh->nMaterials >> ctemp >> itemp >> ctemp;
					M_Material * M;
					for (short i = 0; i < _Mesh->nMaterials; i++)
					{
						M = new M_Material;
						M->Material_ID = i;
						_Mesh->MaterialList.push_back(M);
					}
					for (int i = 0; i < _Mesh->IndexSize; i++)
					{
						Xfile >> stemp >> ctemp;
						for (int j = 0; j < _Mesh->MaterialList.size(); j++)
						{
							if (stemp == _Mesh->MaterialList[j]->Material_ID)
							{
								_Mesh->MaterialList[j]->Material_Index.push_back(_Mesh->Indices[i]);
							}
						}
					}
					MeshList.push_back(_Mesh);
				}
			}
		}
		Xfile.close();
	}
}