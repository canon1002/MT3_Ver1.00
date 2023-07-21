// エンジンコード インクルード
#include <Novice.h>
#include <ImGuiManager.h>

// 自作コード インクルード
#include"./Code/hedaer/MathTool.h"
#include"./Code/hedaer/MatrixCamera.h"

const char kWindowTitle[] = "LD2A_12_ワタナベユウタ_";
const float kWindowSizeX = 1280.0f;
const float kWindowSizeY = 720.0f;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, int(kWindowSizeX), int(kWindowSizeY));

	// ワールドの拡縮・回転・平行移動を設定
	Vector3 scale = { 1.0f,1.0f,1.0f };
	Vector3 rotate = { 0.0f,0.0f,0.0f };
	Vector3 translate = { 0.0f,0.0f,0.0f };

	// カメラの拡縮・回転・平行移動を設定
	Vector3 cameraScale = { 1.0f,1.0f,1.0f };
	Vector3 cameraRotate = { 0.4f,0.3f,0.0f };
	Vector3 cameraPosition = { -3.0f,4.0f,-8.00f };

	// 行列カメラのクラスを宣言・初期化
	MatrixCamera* camera = new MatrixCamera({ kWindowSizeX,kWindowSizeY });
	camera->Initialize();

	// 表示用の変数
	//const int kRowHeight = 30;
	//const int kColumnWidth = 600;

	//
	// 課題用変数　ここから
	//

	// 線
	Segment segment = { {1.0f,1.0f,0.0f} ,{1.0f,1.0f,0.0f} };
	Line line = { {-1.0f,-1.0f,1.0f} ,{2.0f,4.0f,1.0f} };
	Ray ray = { {-.0f,1.0f,0.0f} ,{1.0f,1.0f,2.0f} };
	Vector3 segmentPos[2],linePos[2],rayPos[2];

	// 平面
	Plane plane = { {0.0f,1.0f,0.0f},1.0f };

	// 球体の色
	uint32_t color = 0xFFFFFFFF;
	uint32_t colorL = 0xFFFFFFFF;
	uint32_t colorR = 0xFFFFFFFF;

	//
	//　課題用変数　ここまで
	//


	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Vector2Int mousePos = { 0,0 };
	Vector2Int preMousePos = { 0,0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		// マウスの入力を受け取る
		preMousePos = mousePos;
		Novice::GetMousePosition(&mousePos.x, &mousePos.y);

		///
		/// ↓更新処理ここから
		///

		// マウス右クリック+カーソル移動で回転
		if (Novice::IsPressMouse(1)) {

			if (0 < (preMousePos.x - mousePos.x)) {
				cameraRotate.y += 0.01f;
			}

			if (0 > (preMousePos.x - mousePos.x)) {
				cameraRotate.y -= 0.01f;
			}

			if (0 < (preMousePos.y - mousePos.y)) {
				cameraRotate.x += 0.01f;
			}

			if (0 > (preMousePos.y - mousePos.y)) {
				cameraRotate.x -= 0.01f;
			}

		}

		// マウス中クリック+カーソル移動で平行移動
		if (Novice::IsPressMouse(2)) {

			if (0 < (preMousePos.x - mousePos.x)) {
				cameraPosition.x += 0.1f;
			}

			if (0 > (preMousePos.x - mousePos.x)) {
				cameraPosition.x -= 0.1f;
			}

			if (0 < (preMousePos.y - mousePos.y)) {
				cameraPosition.y -= 0.1f;
			}

			if (0 > (preMousePos.y - mousePos.y)) {
				cameraPosition.y += 0.1f;
			}

		}

		// imGuiによる関数表示

		ImGui::Begin("Setting");
		ImGui::Text("MousePosition(%d,%d)",mousePos.x,mousePos.y);
		ImGui::SliderFloat3("Camera Translate", &cameraPosition.x, -5.0f, 5.0f);
		ImGui::SliderFloat3("Camera Rotate", &cameraRotate.x, -1.0f, 1.0f);
		ImGui::SliderFloat3("Camera Scale", &cameraScale.x, 0.1f, 2.0f);
		ImGui::End();

		ImGui::Begin("Window");
		ImGui::DragFloat3("Plane.Nomal", &plane.normal.x, 0.01f);
		ImGui::DragFloat3("Segment.Origin", &segment.origin.x, 0.01f);
		ImGui::DragFloat3("Segment.Diff", &segment.diff.x, 0.01f);
		ImGui::DragFloat3("Line.Origin", &line.origin.x, 0.01f);
		ImGui::DragFloat3("Line.Diff", &line.diff.x, 0.01f);
		ImGui::DragFloat3("Ray.Origin", &ray.origin.x, 0.01f);
		ImGui::DragFloat3("Ray.Diff", &ray.diff.x, 0.01f);
		ImGui::End();
		plane.normal = Nomalize(plane.normal);

		// カメラの更新
		camera->SetWorldAffine(scale, rotate, translate);
		camera->SetCameraAffine(cameraScale, cameraRotate, cameraPosition);
		camera->Update();

		// 座標変換
		segmentPos[0] = camera->GetScreenPos(camera->GetNdcPos(segment.origin));
		segmentPos[1] = camera->GetScreenPos(camera->GetNdcPos(Add(segment.origin, segment.diff)));
		linePos[0] = camera->GetScreenPos(camera->GetNdcPos(line.origin));
		linePos[1] = camera->GetScreenPos(camera->GetNdcPos(Add(line.origin, line.diff)));
		rayPos[0] = camera->GetScreenPos(camera->GetNdcPos(ray.origin));
		rayPos[1] = camera->GetScreenPos(camera->GetNdcPos(Add(ray.origin, ray.diff)));

		// 衝突判定を行い、接触していたら色を赤色に変更
		if (isCollision(segment, plane)) {
			color = RED;
		}
		else {
			color = WHITE;
		}

		if (isCollision(line, plane)) {
			colorL = RED;
		}
		else {
			colorL = WHITE;
		}

		if (isCollision(ray, plane)) {
			colorR = RED;
		}
		else {
			colorR = WHITE;
		}


		///
		/// ↑更新処理ここまで
		///



		///
		/// ↓描画処理ここから
		///


		// 描画
		

		// グリッド
		DrawGrid(camera->GetViewprojectionMatrix(), camera->GetViewportMatrix());

		Novice::DrawLine(
			(int)segmentPos[0].x, (int)segmentPos[0].y,
			(int)segmentPos[1].x, (int)segmentPos[1].y,
			color
		);

		Novice::DrawLine(
			(int)linePos[0].x, (int)linePos[0].y,
			(int)linePos[1].x, (int)linePos[1].y,
			colorL
		);

		Novice::DrawLine(
			(int)rayPos[0].x, (int)rayPos[0].y,
			(int)rayPos[1].x, (int)rayPos[1].y,
			colorR
		);

		// 球体の描画
		for (int i = 0; i < 2; i++) {
			Novice::DrawEllipse(segmentPos[i].x, segmentPos[i].y, 8, 8, 0.0f, BLUE, kFillModeSolid);
			Novice::DrawEllipse(linePos[i].x, linePos[i].y, 8, 8, 0.0f, GREEN, kFillModeSolid);
			Novice::DrawEllipse(rayPos[i].x, rayPos[i].y, 8, 8, 0.0f, 0xFF00FFFF, kFillModeSolid);
		}

		DrawPlane(plane,
			camera->GetViewprojectionMatrix(),
			camera->GetViewportMatrix(),
			color
		);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	delete camera;

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}