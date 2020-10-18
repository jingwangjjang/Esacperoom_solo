#include <bangtal>
using namespace bangtal;

int main() {
	ScenePtr lab = Scene::create("Lab", "RoomEscape/������_��ü.jpg");
	ScenePtr lab_desk = Scene::create("Lab_desk", "RoomEscape/������_å��.jpg");
	ScenePtr lab_ondesk = Scene::create("Lab_ondesk", "RoomEscape/������_å����.jpg");

	auto lab_to_desk = Object::create("RoomEscape/����ȭ��ǥ.png", lab, 770, 350);
	lab_to_desk->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		lab_desk->enter();

		return true;
		});

	auto desk_to_lab = Object::create("RoomEscape/�Ʒ�ȭ��ǥ.png", lab_desk, 1000, 20);
	desk_to_lab->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		lab->enter();

		return true;
		});

	auto desk_to_ondesk = Object::create("RoomEscape/�Ʒ�ȭ��ǥ.png", lab_desk, 500, 300);
	desk_to_lab->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		lab_ondesk->enter();

		return true;
		});

}