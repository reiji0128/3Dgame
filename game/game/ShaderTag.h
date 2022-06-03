#pragma once
#include <string>
#include <stdexcept>
#include <iterator>

// �K�p����V�F�[�_�[�̃^�O
// Begien��End�̊Ԃ�255�܂Œ�`�ł���
enum class ShaderTag : unsigned char
{
	Begin,                                    // Tag�̊J�n�}�[�J�[ (Begin����O�ɒ�`���Ă͂Ȃ�Ȃ�)
						                      
	Sprite,                                   // �X�v���C�g�V�F�[�_�[
	Tilemap,                                  // �^�C���}�b�v�V�F�[�_�[
	Phong,                                    // �t�H�O�V�F�[�_�[
	DepthmapAndShadowMap,                     // �f�v�X�}�b�v�ƃV���h�E�}�b�v (���b�V���p)
	SkinnedDepthmapAndSkinnedShadowMap,       // �f�v�X�}�b�v�ƃV���h�E�}�b�v (�X�P���^�����b�V���p)
	HDRBloomBlend,                            // HDR��Bloom�̃u�����h�V�F�[�_�[
						                      
	None,                                     // �K�p����V�F�[�_�[�Ȃ�
						                      
	End                                       // Tag�̏I���}�[�J�[ (End����ɒ�`���Ă͂Ȃ�Ȃ�)
};

// �O�u�C���N�������g
ShaderTag& operator ++(ShaderTag& rhs);