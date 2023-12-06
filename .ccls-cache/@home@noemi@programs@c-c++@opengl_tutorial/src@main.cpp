#include <engine/Window.hpp>
#include <iostream>
#include <vector>

class PhysicsWorld : public eng::Window
{
private:
	 std::vector<void*> m_objects;
public:
	 PhysicsWorld();
	 ~PhysicsWorld() = default;

	 void on_create() override {
		  
	 }

	 void on_update(float elapsed_time) override {
		  
	 }
};

int main()
{
	 eng::Window window(640, 640, "Hello");
	 window.run();

	 return 0;
}
