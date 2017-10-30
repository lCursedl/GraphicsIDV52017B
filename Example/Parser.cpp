#include "Parser.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


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
				int LineTexturePath = Xline.find("TextureFilename Diffuse");
				float * TempVec;
				float * TempNrml;
				float * TempTxt;
				int MaterialID = 0;

				if (LineMesh != -1)
				{
					_Mesh = new Mesh;
					//Cantidad de vertices
					Xfile >> _Mesh->VertexSize >> ctemp;
					_Mesh->Vertices = new CVertex4[_Mesh->VertexSize];
					for (int i = 0; i < _Mesh->VertexSize; i++)
					{
						//X
						Xfile >> _Mesh->Vertices[i].x >> ctemp;

						//Y
						Xfile >> _Mesh->Vertices[i].y >> ctemp;

						//Z
						Xfile >> _Mesh->Vertices[i].z >> ctemp;

						//W = 1.0
						Xfile >> ctemp;
					}
					//Dinamic vertex
					/*TempVec = new float[_Mesh->VertexSize * (_Mesh->Stride / 4)];
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
					}*/

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
					_Mesh->Stride += 16;
					//TempNrml = new float[_Mesh->VertexSize * 4];
					//Normales
					Xfile >> _Mesh->VertexSize >> ctemp;
					for (int i = 0; i < _Mesh->VertexSize; i++)
					{
						//NX
						Xfile >> _Mesh->Vertices[i].nx >> ctemp;

						//NY
						Xfile >> _Mesh->Vertices[i].ny >> ctemp;

						//NZ
						Xfile >> _Mesh->Vertices[i].nz >> ctemp; 

						Xfile >> ctemp;
					}
					//Dinamic normals
					//for (int i = 0; i < _Mesh->VertexSize * 4; i++)
					//{
					//	//NX
					//	Xfile >> TempNrml[i] >> ctemp;
					//	i++;
					//	//NY
					//	Xfile >> TempNrml[i] >> ctemp;
					//	i++;
					//	//NZ
					//	Xfile >> TempNrml[i] >> ctemp;
					//	Xfile >> ctemp;
					//	i++;
					//	//NW
					//	TempNrml[i] = 1.0f;
					//}
				}

				if (LineTextCoords != -1)
				{
					//Coordenadas de textura
					Xfile >> _Mesh->VertexSize >> ctemp;
					for (int i = 0; i < _Mesh->VertexSize; i++)
					{
						//U
						Xfile >> _Mesh->Vertices[i].u >> ctemp;

						//V
						Xfile >> _Mesh->Vertices[i].v >> ctemp;
						Xfile >> ctemp;

					}
					//Dinamic Texcoords
					//_Mesh->Stride += 8;
					//for (int i = 0; i < _Mesh->VertexSize * (_Mesh->Stride / 4); i++)
					//{
					//	//U
					//	Xfile >> _Mesh->Vertex[i] >> ctemp;
					//	i++;
					//	//V
					//	Xfile >> _Mesh->Vertex[i] >> ctemp >> ctemp;
					//}
				}

				if (LineMaterials != -1)
				{
					Xfile >> _Mesh->nMaterials >> ctemp >> itemp >> ctemp;
					material_count = _Mesh->nMaterials;
					M_Material * M;
					for (int i = 0; i < _Mesh->nMaterials; i++) 
					{
						M = new M_Material;
						M->Material_ID = i;
						_Mesh->MaterialList.push_back(M);
					}
					for (int i = 0; i < itemp * 3; i++)
					{
						Xfile >> stemp >> ctemp;
						for (int j = 0; j < _Mesh->MaterialList.size(); j++)
						{
							if (stemp == _Mesh->MaterialList[j]->Material_ID)
							{
								_Mesh->MaterialList[j]->Material_Index.push_back(_Mesh->Indices[i]);
								_Mesh->MaterialList[j]->MIndex[1] = _Mesh->Indices[i];
								i++;

								_Mesh->MaterialList[j]->Material_Index.push_back(_Mesh->Indices[i]);
								i++;

								_Mesh->MaterialList[j]->Material_Index.push_back(_Mesh->Indices[i]);
								_Mesh->MaterialList[j]->IndexSize += 3;
							}
						}
					}
					
				}
				if (LineTexturePath != -1)
				{
					Xfile >> _Mesh->MaterialList[diffuse_count]->DiffusePath;
					_Mesh->MaterialList[diffuse_count]->DiffusePath = _Mesh->MaterialList[diffuse_count]->DiffusePath.substr(1, _Mesh->MaterialList[diffuse_count]->DiffusePath.size() - 3);
					diffuse_count++;
				}

				if (diffuse_count == material_count)
				{
					diffuse_count = 0;
					while (diffuse_count < _Mesh->MaterialList.size())
					{
						int x = 0, y = 0, channels = 0;
						unsigned char *buffer = stbi_load(_Mesh->MaterialList[diffuse_count]->DiffusePath.c_str(), &x, &y, &channels, 0);

#ifdef USING_OPENGL_ES
						glGenTextures(1, &_Mesh->MaterialList[diffuse_count]->diffuse_textID);
						glBindTexture(GL_TEXTURE_2D, _Mesh->MaterialList[diffuse_count]->diffuse_textID);

						glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
						glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)(buffer));
						glGenerateMipmap(GL_TEXTURE_2D);
#elif defined(USING_D3D11)

						D3D11_TEXTURE2D_DESC desc = { 0 };
						desc.Width = x;
						desc.Height = y;
						desc.ArraySize = 1;
						desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
						desc.SampleDesc.Count = 1;
						desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
						desc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

						D3D11_SUBRESOURCE_DATA initData{};
						initData.pSysMem = buffer;
						initData.SysMemPitch = sizeof(unsigned char) * x * 4;

						D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};
						srvDesc.Format = desc.Format;
						srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
						srvDesc.Texture2D.MipLevels = -1;

						HRESULT hr = D3D11Device->CreateTexture2D(&desc, nullptr, _Mesh->MaterialList[diffuse_count]->Tex.GetAddressOf());
						if (hr != S_OK) {
							_Mesh->MaterialList[diffuse_count]->Material_ID = -1;
							std::cout << "Error creating Texture D3DDevice" << std::endl;
						}

						D3D11Device->CreateShaderResourceView(_Mesh->MaterialList[diffuse_count]->Tex.Get(), &srvDesc, _Mesh->MaterialList[diffuse_count]->pSRVTex.GetAddressOf());
						D3D11DeviceContext->UpdateSubresource(_Mesh->MaterialList[diffuse_count]->Tex.Get(), 0, 0, buffer, initData.SysMemPitch, 0);
						D3D11DeviceContext->GenerateMips(_Mesh->MaterialList[diffuse_count]->pSRVTex.Get());
#endif
						++diffuse_count;
					}
					diffuse_count = 0;
					MeshList.push_back(_Mesh);
				}
			}
		}
		Xfile.close();
	}
}