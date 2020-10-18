#include <bangtal>

using namespace bangtal;

int main() {
	ScenePtr lab = Scene::create("Lab", "RoomEscape/연구실_전체.jpg");
	ScenePtr lab_desk = Scene::create("Lab_desk", "RoomEscape/연구실_책상.jpg");
	ScenePtr lab_ondesk = Scene::create("Lab_ondesk", "RoomEscape/연구실_책상위.jpg");
	ScenePtr lab_hallway = Scene::create("Lab_hallway", "RoomEscape/연구실_정면복도.jpg");
	ScenePtr lab_rest = Scene::create("Lab_rest", "RoomEscape/연구실_휴게실.jpg");
	ScenePtr lab_resttv = Scene::create("Lab_resttv", "RoomEscape/연구실_휴게실티비.jpg");
	ScenePtr lab_lefthallway = Scene::create("Lab_lefthallway", "RoomEscape/연구실_왼쪽복도.jpg");

	SoundPtr woo_vu_luvub_dub_dub = Sound::create("Sounds/woo_vu_luvub_dub_dub.wav");
	SoundPtr owee = Sound::create("Sounds/owee.mp3");
	SoundPtr get_item = Sound::create("Sounds/획득.mp3");
	SoundPtr hit = Sound::create("Sounds/퍽.mp3");
	SoundPtr teleport = Sound::create("Sounds/vwoop.mp3");
	SoundPtr death = Sound::create("Sounds/death.mp3");
	SoundPtr scream = Sound::create("Sounds/scream.mp3");
	SoundPtr portal_open = Sound::create("Sounds/portal_open.mp3");

	TimerPtr timer = Timer::create(30.f);

	timer->setOnTimerCallback([&](TimerPtr timer)->bool {

		endGame();

		return true;
	});

	auto lab_to_desk = Object::create("RoomEscape/왼쪽화살표.png", lab, 770, 350);
	lab_to_desk->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		lab_desk->enter();

		return true;
	});

	auto lab_to_hallway = Object::create("RoomEscape/위화살표.png", lab, 1000, 270);
	lab_to_hallway->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		lab_hallway->enter();

		return true;
	});

	auto lab_to_lefthallway = Object::create("RoomEscape/왼쪽화살표.png", lab, 300, 250);
	lab_to_lefthallway->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		lab_lefthallway->enter();

		return true;
	});

	auto lefthallway_to_lab = Object::create("RoomEscape/아래화살표.png", lab_lefthallway, 750, 30);
	lefthallway_to_lab->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		lab->enter();

		return true;
	});

	auto desk_to_lab = Object::create("RoomEscape/아래화살표.png", lab_desk, 1000, 20);
	desk_to_lab->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		lab->enter();

		return true;
	});

	auto desk_to_ondesk = Object::create("RoomEscape/아래화살표.png", lab_desk, 500, 300);
	desk_to_ondesk->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		lab_ondesk->enter();

		return true;
	});
	desk_to_ondesk->hide();

	auto ondesk_to_desk = Object::create("RoomEscape/아래화살표.png", lab_ondesk, 900, 20);
	ondesk_to_desk->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		lab_desk->enter();

		return true;
	});

	auto hallway_to_lab = Object::create("RoomEscape/아래화살표.png", lab_hallway, 500, 20);
	hallway_to_lab->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		lab->enter();

		return true;
	});

	auto hallway_to_rest = Object::create("RoomEscape/왼쪽화살표.png", lab_hallway, 20, 250);
	hallway_to_rest->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		lab_rest->enter();

		return true;
	});

	auto rest_to_hallway = Object::create("RoomEscape/아래화살표.png", lab_rest, 500, 20);
	rest_to_hallway->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		lab_hallway->enter();

		return true;
	});

	auto rest_to_resttv = Object::create("RoomEscape/왼쪽화살표.png", lab_rest, 700, 350);
	rest_to_resttv->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		lab_resttv->enter();

		return true;
	});

	auto resttv_to_rest = Object::create("RoomEscape/아래화살표.png", lab_resttv, 600, 10);
	resttv_to_rest->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		lab_rest->enter();

		return true;
	});

	auto nightmare = Object::create("RoomEscape/악몽.png", lab, 600, 100);
	int nightmare_msg_count = 0;
	nightmare->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (nightmare_msg_count == 0) {
			showMessage("악몽: 이정도 쯤이야 쉽게 피하지");
			teleport->play();
			nightmare->locate(lab_rest, 1000, 100);
			lab->setLight(1);
			lab_rest->setLight(0.3f);
			nightmare_msg_count++;
		}
		else if(nightmare_msg_count == 1) {
			showMessage("악몽: 천천히 잠식해라..");
			teleport->play();
			nightmare->locate(lab_lefthallway, 750, 150);
			lab_rest->setLight(1);
			lab_lefthallway->setLight(0.3f);
			nightmare_msg_count++;
		}
		else {
			showMessage("악몽: 참 끈질기군.. 다음에 두고보자");
			death->play();
			lab_lefthallway->setLight(1);
			nightmare->hide();
			timer->stop();
			hideTimer();
		}

		return true;
	});
	nightmare->hide();

	auto portal = Object::create("RoomEscape/포탈.png", lab, 400, 100);
	portal->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		endGame();

		return true;
	});
	portal->hide();

	auto rick = Object::create("RoomEscape/릭.png", lab, 50, 50);
	bool drunk = true; //릭이 취했는지 확인
	bool portalgun = false; //포탈용액을 만들었는지 확인
	int rick_msg_count = 0;
    rick->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		
		if (portalgun == true) {
			showMessage("릭: 잘했어 모티! 이제 모험을 떠나볼까?\n 포탈을 열어뒀으니 들어가자");
			portal_open->play();
			portal->show();
		}
		else if (drunk == true) {
			showMessage("릭: 으.. 모티 나 너무 취했어..\n 정신좀 차리게 도와줘..");
		}
		else {
			if (rick_msg_count == 0) {
				showMessage("릭: 이제 정신이좀 드네!\n 우리 오늘 모험가기로 했었지? 준비하자");
				rick_msg_count++;
			}
			else if (rick_msg_count == 1) {
				showMessage("릭: 근데 포탈건의 용액이 다 떨어져버렸어.. 좀 도와줄래?");
				rick_msg_count++;
			}
			else if (rick_msg_count == 2) {
				showMessage("릭: 휴게실 어딘가에 만드는 방법을 적어둔거 같은데..\n 숙취때문에 힘드니 너가 좀 만들어서 갖다줘");
			}
		}
		woo_vu_luvub_dub_dub->play();

        return true;
    });

	auto letter = Object::create("RoomEscape/편지봉투.png", lab, 800, 70);
	letter->setScale(0.7f);
	letter->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		showImageViewer("RoomEscape/편지내용.jpg");

		return true;
	});

	auto poopybutthole = Object::create("RoomEscape/푸피벗홀.webp", lab_desk, 700, 50);
	poopybutthole->setScale(0.5f);
	int poopybutthole_msg_count = 0;
	poopybutthole->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (poopybutthole_msg_count == 0) {
			showMessage("푸피벗홀: 릭을깨울 방법을 찾고 싶어?");
			poopybutthole_msg_count++;
		}
		else if (poopybutthole_msg_count == 1) {
			showMessage("푸피벗홀: 그렇다면 내가내는 퀴즈를 맞춰봐");
			poopybutthole_msg_count++;
		}
		else if (poopybutthole_msg_count == 2) {
			showMessage("푸피벗홀: 내생일은 언제일까?");
			poopybutthole_msg_count++;
		}
		else if (poopybutthole_msg_count == 3) {
			showKeypad("0714", poopybutthole);
		}
		else {
			showMessage("푸피벗홀: 놀아주러 온거야?");
		}

		owee->play();

		return true;
	});

	poopybutthole->setOnKeypadCallback([&](ObjectPtr object)->bool {
		
		showMessage("푸피벗홀: 내 생일을 알아주다니.. 감동이야\n 숙취해소제는 책상앞에 있어");
		desk_to_ondesk->show();
		poopybutthole_msg_count++;

		return true;
	});

	auto hangover_reliever = Object::create("RoomEscape/숙취해소제.png", lab_ondesk, 670, 100);
	hangover_reliever->setScale(0.2f);
	hangover_reliever->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		hangover_reliever->pick();
		get_item->play();
		drunk = false;
		showMessage("숙취해소제를 획득하였다.");

		return true;
	});

	auto green_potion = Object::create("RoomEscape/초록용액.png", lab_hallway, 200, 270);
	green_potion->setScale(0.2f);
	green_potion->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		green_potion->pick();
		get_item->play();
		showMessage("초록용액을 획득하였다.");

		return true;
	});

	auto summer = Object::create("RoomEscape/써머.png", lab_hallway, 180, 200);
	summer->setScale(0.34f);
	summer->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		showMessage("써머: 모티 여기서 뭐해? 걸리적거리니까 저리비켜\n 어쭈 째려봐? 이젠 누나 \"밀치기\"라도 하겠어");
		if (action == MouseAction::MOUSE_DRAG_RIGHT) {
			showMessage("써머: 누나를 밀쳐? 너 집에가서 두고봐");
			hit->play();
			summer->hide();
		}

		return true;
	});

	auto yellow_potion = Object::create("RoomEscape/노랑용액.png", lab_rest, 1100, 100);
	yellow_potion->setScale(0.2f);
	yellow_potion->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		yellow_potion->pick();
		get_item->play();
		showMessage("노랑용액을 획득하였다.");

		return true;
	});

	auto notepad = Object::create("RoomEscape/메모장.png", lab_resttv, 580, 270);
	notepad->setScale(0.35f);

	auto red_potion = Object::create("RoomEscape/빨강용액.png", lab, 0, 0, false);
	red_potion->setScale(0.2f);

	auto safe = Object::create("RoomEscape/금고.png", lab_lefthallway, 750, 200);
	safe->setScale(0.5f);
	safe->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		showKeypad("morty", safe);

		return true;
	});

	safe->setOnKeypadCallback([&](ObjectPtr object)->bool {
		
		red_potion->pick();
		get_item->play();
		showMessage("빨강용액을 획득하였다.");
		safe->hide();

		return true;
	});

	auto blue_potion = Object::create("RoomEscape/파랑용액.png", lab_resttv, 1170, 248);
	blue_potion->setScale(0.2f);
	blue_potion->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		blue_potion->pick();
		get_item->play();
		showMessage("파랑용액을 획득하였다.");

		return true;
	});

	auto gun = Object::create("RoomEscape/총.png", lab, 0, 0, false);
	gun->setScale(0.3f);

	gun->defineCombination(red_potion, blue_potion);

	gun->setOnCombineCallback([&](ObjectPtr object)->bool {

		scream->play();
		showMessage("이건 악몽소환용액이잖아..!\n 큰일나기전에 빨리 총으로 악몽을 처리하자");
		nightmare->show();
		lab->setLight(0.3f);
		timer->start();
		showTimer(timer);

		return true;
	});

	auto portar_liquid = Object::create("RoomEscape/포탈용액.png", lab, 0, 0, false);
	portar_liquid->setScale(0.3f);

	portar_liquid->defineCombination(yellow_potion, green_potion);

	portar_liquid->setOnCombineCallback([&](ObjectPtr object)->bool {

		get_item->play();
		portalgun = true;
		showMessage("포탈용액을 획득하였다.\n 할아버지에게 가져다 주자.");

		return true;
	});

	startGame(lab);
	return 0;
}