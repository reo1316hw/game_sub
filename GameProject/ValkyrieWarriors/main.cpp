#include "pch.h"

/// <summary>
/// �N���X���ł̐錾���Ԃ�public>protected>private>public(GetSet)�̏�
/// </summary>

/// <summary>
/// main�֐�
/// </summary>
/// <param name="argc"> �R�}���h���C�������̐� </param>
/// <param name="argv"> �R�}���h���C������ </param>
/// <returns> �I�����邩 </returns>
int main(int argc, char** argv)
{
	//�Q�[���N���X�̒�`
	Game game;
	//�Q�[���N���X�̏�����������������
	bool success = game.Initialize();
	game.SetFirstScene(new TitleScene());
	if (success)
	{
		game.GameLoop();
	}
	//�Q�[���N���X�̏I������
	game.Termination();

	return 0;
}