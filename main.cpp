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

	// AABB
	AABB aabb1{
		{-0.5f,-0.5f,-0.5f},
		{0.0f,0.0f,0.0f},
	};

	AABB aabb2 = {
		{0.2f,0.2f,0.2f},
		{1.0f,1.0f,1.0f},
	};

	// 色
	uint32_t color = 0xFFFFFFFF;

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
		ImGui::SliderFloat3("aabb1 max", &aabb1.max.x, -2.0f, 2.0f);
		ImGui::SliderFloat3("aabb1 min", &aabb1.min.x, -2.0f, 2.0f);
		ImGui::SliderFloat3("aabb2 max", &aabb2.max.x, -2.0f, 2.0f);
		ImGui::SliderFloat3("aabb2 min", &aabb2.min.x, -2.0f, 2.0f);
		ImGui::End();
		
		aabb1.min.x = (std::min)(aabb1.min.x, aabb1.max.x);
		aabb1.max.x = (std::max)(aabb1.min.x, aabb1.max.x);
		aabb1.min.y = (std::min)(aabb1.min.y, aabb1.max.y);
		aabb1.max.y = (std::max)(aabb1.min.y, aabb1.max.y);
		aabb1.min.z = (std::min)(aabb1.min.z, aabb1.max.z);
		aabb1.max.z = (std::max)(aabb1.min.z, aabb1.max.z);

		aabb2.min.x = (std::min)(aabb2.min.x, aabb2.max.x);
		aabb2.max.x = (std::max)(aabb2.min.x, aabb2.max.x);
		aabb2.min.y = (std::min)(aabb2.min.y, aabb2.max.y);
		aabb2.max.y = (std::max)(aabb2.min.y, aabb2.max.y);
		aabb2.min.z = (std::min)(aabb2.min.z, aabb2.max.z);
		aabb2.max.z = (std::max)(aabb2.min.z, aabb2.max.z);
		


		// カメラの更新
		camera->SetWorldAffine(scale, rotate, translate);
		camera->SetCameraAffine(cameraScale, cameraRotate, cameraPosition);
		camera->Update();


		// 衝突判定を行い、接触していたら色を赤色に変更
		if (IsCollision(aabb1,aabb2)) {
			color = RED;
		}
		else {
			color = WHITE;
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

		DrawAABB(aabb1, camera->GetViewprojectionMatrix(), camera->GetViewportMatrix(), color);
		DrawAABB(aabb2, camera->GetViewprojectionMatrix(), camera->GetViewportMatrix(), color);

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