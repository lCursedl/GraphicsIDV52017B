#include "Mesh.h"
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

void MeshGL::Create(char * filename) {
#ifdef USING_OPENGL_ES

	shaderID = glCreateProgram();

	char *vsSourceP = file2string("VS_Mesh.glsl");
	char *fsSourceP = file2string("FS_Mesh.glsl");

	GLuint vshader_id = createShader(GL_VERTEX_SHADER, vsSourceP);
	GLuint fshader_id = createShader(GL_FRAGMENT_SHADER, fsSourceP);

	glAttachShader(shaderID, vshader_id);
	glAttachShader(shaderID, fshader_id);

	glLinkProgram(shaderID);
	glUseProgram(shaderID);

	vertexAttribLoc = glGetAttribLocation(shaderID, "Vertex");
	normalAttribLoc = glGetAttribLocation(shaderID, "Normal");
	uvAttribLoc = glGetAttribLocation(shaderID, "UV");

	diffuseAttribLoc = glGetUniformLocation(shaderID, "Diffuse");
	lightposLoc = glGetUniformLocation(shaderID, "LightPos");
	matWorldViewProjUniformLoc = glGetUniformLocation(shaderID, "WVP");
	matWorldUniformLoc = glGetUniformLocation(shaderID, "World");

	P.Parse(filename, MyMeshes);

	for (int i = 0; i < MyMeshes.size(); i++)
	{
		glGenBuffers(1, &MyMeshes[i]->VB);
		glBindBuffer(GL_ARRAY_BUFFER, MyMeshes[i]->VB);
		glBufferData(GL_ARRAY_BUFFER, MyMeshes[i]->VertexSize * sizeof(CVertex4), MyMeshes[i]->Vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		for (int j = 0; j < MyMeshes[i]->nMaterials; j++)
		{
			glGenBuffers(1, &MyMeshes[i]->MaterialList[j]->IB);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, MyMeshes[i]->MaterialList[j]->IB);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, MyMeshes[i]->MaterialList[j]->IndexSize * sizeof(unsigned short), &MyMeshes[i]->MaterialList[j]->Material_Index[0], GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
	transform = Identity();
#elif defined(USING_D3D11)
	char *vsSourceP = file2string("VS.hlsl");
	char *fsSourceP = file2string("FS.hlsl");

	if (!vsSourceP || !fsSourceP)
		exit(32);	

	HRESULT hr;
	{
		VS_blob = nullptr;
		ComPtr<ID3DBlob> errorBlob = nullptr;
		hr = D3DCompile(vsSourceP, (UINT)strlen(vsSourceP), 0, 0, 0, "VS", "vs_5_0", 0, 0, &VS_blob, &errorBlob);
		if (hr != S_OK) {

			if (errorBlob) {
				printf("errorBlob shader[%s]", (char*)errorBlob->GetBufferPointer());
				return;
			}

			if (VS_blob) {
				return;
			}
		}

		hr = D3D11Device->CreateVertexShader(VS_blob->GetBufferPointer(), VS_blob->GetBufferSize(), 0, &pVS);
		if (hr != S_OK) {
			printf("Error Creating Vertex Shader\n");
			return;
		}
	}

	{
		FS_blob = nullptr;
		ComPtr<ID3DBlob> errorBlob = nullptr;
		hr = D3DCompile(fsSourceP, (UINT)strlen(fsSourceP), 0, 0, 0, "FS", "ps_5_0", 0, 0, &FS_blob, &errorBlob);
		if (hr != S_OK) {
			if (errorBlob) {
				printf("errorBlob shader[%s]", (char*)errorBlob->GetBufferPointer());
				return;
			}

			if (FS_blob) {
				return;
			}
		}

		hr = D3D11Device->CreatePixelShader(FS_blob->GetBufferPointer(), FS_blob->GetBufferSize(), 0, &pFS);
		if (hr != S_OK) {
			printf("Error Creating Pixel Shader\n");
			return;
		}
	}
	
	free(vsSourceP);
	free(fsSourceP);

	P.Parse(filename, MyMeshes);

	D3D11DeviceContext->VSSetShader(pVS.Get(), 0, 0);
	D3D11DeviceContext->PSSetShader(pFS.Get(), 0, 0);

	D3D11_INPUT_ELEMENT_DESC vertexDeclaration[] = {
		{ "POSITION" , 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL"   , 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD" , 0, DXGI_FORMAT_R32G32_FLOAT,       0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	hr = D3D11Device->CreateInputLayout(vertexDeclaration, ARRAYSIZE(vertexDeclaration), VS_blob->GetBufferPointer(), VS_blob->GetBufferSize(), &Layout);
	if (hr != S_OK) {
		printf("Error Creating Input Layout\n");
		return;
	}

	D3D11DeviceContext->IASetInputLayout(Layout.Get());

	D3D11_BUFFER_DESC bdesc = { 0 };
	bdesc.Usage = D3D11_USAGE_DEFAULT;
	bdesc.ByteWidth = sizeof(MeshGL::CBuffer);
	bdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	hr = D3D11Device->CreateBuffer(&bdesc, 0, pd3dConstantBuffer.GetAddressOf());
	if (hr != S_OK) {
		printf("Error Creating Buffer Layout\n");
		return;
	}

	D3D11DeviceContext->VSSetConstantBuffers(0, 1, pd3dConstantBuffer.GetAddressOf());
	D3D11DeviceContext->PSSetConstantBuffers(0, 1, pd3dConstantBuffer.GetAddressOf());


	/*CTextureD3D *texd3d = dynamic_cast<CTextureD3D*>(tex);
	D3D11DeviceContext->PSSetShaderResources(0, 1, texd3d->pSRVTex.GetAddressOf());
	D3D11DeviceContext->PSSetSamplers(0, 1, texd3d->pSampler.GetAddressOf());*/

	for (int i = 0; i < MyMeshes.size(); i++)
	{
		bdesc = { 0 };
		bdesc.ByteWidth = sizeof(CVertex4) * MyMeshes[i]->VertexSize;
		bdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		D3D11_SUBRESOURCE_DATA subData = { MyMeshes[i]->Vertices, 0, 0 };

		hr = D3D11Device->CreateBuffer(&bdesc, &subData, &MyMeshes[i]->VB);
		if (hr != S_OK)
		{
			printf("Error Creating Vertex Buffer\n");
			return;
		}

		for (int j = 0; j < MyMeshes[i]->nMaterials; j++)
		{
			bdesc = { 0 };
			bdesc.ByteWidth = MyMeshes[i]->MaterialList[j]->IndexSize * sizeof(USHORT);
			bdesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

			subData = {&MyMeshes[i]->MaterialList[j]->Material_Index[0], 0, 0 };

			hr = D3D11Device->CreateBuffer(&bdesc, &subData, &MyMeshes[i]->MaterialList[j]->IB);
			if (hr != S_OK)
			{
				printf("Error Creating Index Buffer\n");
				return;
			}
		}
	}

	transform = Identity();

#endif	
}

void MeshGL::Transform(float *t)
{
	transform = t;
}

void MeshGL::Draw(float *t, float *vp)
{
#ifdef USING_OPENGL_ES
	glUseProgram(shaderID);

	if (t)
	{
		transform = t;
	}
	MATRIX4D VP = MATRIX4D(vp);
	MATRIX4D WVP = transform*VP;

	glUniformMatrix4fv(matWorldUniformLoc, 1, GL_FALSE, &transform.m[0][0]);
	glUniformMatrix4fv(matWorldViewProjUniformLoc, 1, GL_FALSE, &WVP.m[0][0]);

	//VECTOR4D PosLight(-15.0f, 0.0f, 0.0f);

	//glUniform4fv(lightposLoc, 1, &pScProp->LightContainer[0].Position.x);

	for (int i = 0; i < MyMeshes.size(); i++)
	{
		glBindBuffer(GL_ARRAY_BUFFER, MyMeshes[i]->VB);

		glEnableVertexAttribArray(vertexAttribLoc);
		if (normalAttribLoc != -1)
		{
			glEnableVertexAttribArray(normalAttribLoc);
		}

		if (uvAttribLoc != -1)
		{
			glEnableVertexAttribArray(uvAttribLoc);
		}

		glVertexAttribPointer(vertexAttribLoc, 4, GL_FLOAT, GL_FALSE, sizeof(CVertex4), BUFFER_OFFSET(0));


		if (normalAttribLoc != -1)
		{
			glVertexAttribPointer(normalAttribLoc, 4, GL_FLOAT, GL_FALSE, sizeof(CVertex4), BUFFER_OFFSET(16));
		}

		if (uvAttribLoc != -1)
			glVertexAttribPointer(uvAttribLoc, 2, GL_FLOAT, GL_FALSE, sizeof(CVertex4), BUFFER_OFFSET(32));

		for (int j = 0; j < MyMeshes[i]->MaterialList.size(); j++)
		{
			if (diffuseAttribLoc != -1)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, MyMeshes[i]->MaterialList[j]->diffuse_textID);
				glUniform1i(diffuseAttribLoc, 0);
			}
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, MyMeshes[i]->MaterialList[j]->IB);
			glDrawElements(GL_TRIANGLES, MyMeshes[i]->MaterialList[j]->IndexSize, GL_UNSIGNED_SHORT, 0);
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glDisableVertexAttribArray(vertexAttribLoc);

		if (normalAttribLoc != -1)
		{
			glDisableVertexAttribArray(normalAttribLoc);
		}

		if (uvAttribLoc != -1)
		{
			glDisableVertexAttribArray(uvAttribLoc);
		}

	}
	glUseProgram(0);
#elif defined (USING_D3D11)
	if (t)
		transform = t;

	MATRIX4D VP = MATRIX4D(vp);
	MATRIX4D WVP = transform*VP;
	CnstBuffer.WVP = WVP;
	CnstBuffer.World = transform;

	UINT stride = sizeof(CVertex4);
	UINT offset = 0;
	D3D11DeviceContext->VSSetShader(pVS.Get(), 0, 0);
	D3D11DeviceContext->PSSetShader(pFS.Get(), 0, 0);

	D3D11DeviceContext->IASetInputLayout(Layout.Get());

	D3D11DeviceContext->UpdateSubresource(pd3dConstantBuffer.Get(), 0, 0, &CnstBuffer, 0, 0);

	/*TextureD3D *texd3d = dynamic_cast<TextureD3D*>(tex);
	D3D11DeviceContext->PSSetShaderResources(0, 1, texd3d->pSRVTex.GetAddressOf());
	D3D11DeviceContext->PSSetSamplers(0, 1, texd3d->pSampler.GetAddressOf());*/

	D3D11DeviceContext->VSSetConstantBuffers(0, 1, pd3dConstantBuffer.GetAddressOf());
	D3D11DeviceContext->PSSetConstantBuffers(0, 1, pd3dConstantBuffer.GetAddressOf());

	for (int i = 0; i < MyMeshes.size(); i++)
	{
		D3D11DeviceContext->IASetVertexBuffers(0, 1, MyMeshes[i]->VB.GetAddressOf(), &stride, &offset);
		for (int j = 0; j < MyMeshes[i]->nMaterials; j++)
		{
			CTextureD3D *texd3d = dynamic_cast<CTextureD3D*>(MyMeshes[i]->MaterialList[j]->Diffuse);
			D3D11DeviceContext->PSSetShaderResources(0, 1, texd3d->pSRVTex.GetAddressOf());
			D3D11DeviceContext->PSSetSamplers(0, 1, texd3d->pSampler.GetAddressOf());

			D3D11DeviceContext->IASetIndexBuffer(MyMeshes[i]->MaterialList[j]->IB.Get(), DXGI_FORMAT_R16_UINT, 0);
			D3D11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			D3D11DeviceContext->DrawIndexed(MyMeshes[i]->MaterialList[j]->Material_Index.size(), 0, 0);			
		}
	}
#endif // USING_OPENGL_ES	
}

void MeshGL::Destroy() {
#ifdef USING_OPENGL_ES
	glDeleteProgram(shaderID);
#endif // USING_OPENGL_ES	
}