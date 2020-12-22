#include <Ore.h>
#include <glm/gtc/matrix_transform.hpp>

class SandboxLayer : public Ore::Layer {
public:
	SandboxLayer()
		: Layer("Sandbox"), p_Camera(-1.6f, 1.6f, -0.9f, 0.9f), p_CameraPosition(0.0f), p_SQPos(0.0f)
	{
		p_VertexArray.reset(Ore::VertexArray::Create());


		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Ore::VertexBuffer> vertexBuffer;

		vertexBuffer.reset(Ore::VertexBuffer::Create(vertices, sizeof(vertices)));


		Ore::BufferLayout layout = {
			{ Ore::ShaderDataType::Float3, "a_Position" },
			{ Ore::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		p_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Ore::IndexBuffer> indexBuffer;

		indexBuffer.reset(Ore::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		p_VertexArray->SetIndexBuffer(indexBuffer);

		p_SquareVA.reset(Ore::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		std::shared_ptr<Ore::VertexBuffer> squareVB;
		squareVB.reset(Ore::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{ Ore::ShaderDataType::Float3, "a_Position" },
			});
		p_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Ore::IndexBuffer> squareIB;
		squareIB.reset(Ore::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

		p_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;


			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmendeltaTimerc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		p_Shader.reset(new Ore::Shader(vertexSrc, fragmendeltaTimerc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmendeltaTimerc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.6, 1.0);
			}
		)";

		p_BlueShader.reset(new Ore::Shader(blueShaderVertexSrc, blueShaderFragmendeltaTimerc));
	}

	void OnUpdate(Ore::Timestep deltaTime) override {
		if (Ore::Input::IsKeyPressed(ORE_KEY_A))
			p_CameraPosition.x -= p_CameraSpeed * deltaTime;

		else if (Ore::Input::IsKeyPressed(ORE_KEY_D))
			p_CameraPosition.x += p_CameraSpeed * deltaTime;

		if (Ore::Input::IsKeyPressed(ORE_KEY_S))
			p_CameraPosition.y -= p_CameraSpeed * deltaTime;

		else if (Ore::Input::IsKeyPressed(ORE_KEY_W))
			p_CameraPosition.y += p_CameraSpeed * deltaTime;


		Ore::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Ore::RenderCommand::Clear();

		p_Camera.setPosition(p_CameraPosition);

		Ore::Renderer::BeginScene(p_Camera);
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		
		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 20;x++) {
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Ore::Renderer::Submit(p_BlueShader, p_SquareVA, transform);
			}
		}

		//Ore::Renderer::Submit(p_Shader, p_VertexArray);

		Ore::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		
	}

	void OnEvent(Ore::Event& event) override
	{
	}
private:
	std::shared_ptr<Ore::Shader> p_Shader;
	std::shared_ptr<Ore::Shader> p_BlueShader;
	std::shared_ptr<Ore::VertexArray> p_VertexArray;
	std::shared_ptr<Ore::VertexArray> p_SquareVA;

	Ore::OrthographicCamera p_Camera;
	glm::vec3 p_CameraPosition;

	float p_CameraSpeed = 3.0f;
	

};

class Sandbox : public Ore::App {
public:
	Sandbox()
	{
		PushLayer(new SandboxLayer());
	}

	~Sandbox()
	{

	}
};

Ore::App* Ore::CreateApplication() {
	return new Sandbox();
}