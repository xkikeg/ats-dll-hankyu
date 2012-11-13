// 以下の ifdef ブロックは DLL から簡単にエクスポートさせるマクロを作成する標準的な方法です。 
// この DLL 内のすべてのファイルはコマンドラインで定義された ATS_EXPORTS シンボル
// でコンパイルされます。このシンボルはこの DLL が使用するどのプロジェクト上でも未定義でなけ
// ればなりません。この方法ではソースファイルにこのファイルを含むすべてのプロジェクトが DLL 
// からインポートされたものとして ATS_API 関数を参照し、そのためこの DLL はこのマク 
// ロで定義されたシンボルをエクスポートされたものとして参照します。
//#pragma data_seg(".shared")
//#pragma data_seg()

#define ATS_BEACON_SET 0 // 列車種別選別装置
#define ATS_BEACON_ACCEPT 5 // 出発承認合図
#define ATS_BEACON_A 10 // 旧来A点/新型B1点
#define ATS_BEACON_S 11 // 旧来S点/新型B2点/入換15点
#define ATS_BEACON_HP 15 // 新型HP点
#define ATS_BEACON_LP 16 // 新型B3点(LP点)
#define ATS_BEACON_A2 17 // 新型A点

int g_emgBrake; // 非常ノッチ
int g_svcBrake; // 常用最大ノッチ
int g_brakeNotch; // ブレーキノッチ
int g_powerNotch; // 力行ノッチ
int g_reverser; // レバーサ
bool g_pilotlamp; // パイロットランプ
int g_time; // 現在時刻
float g_speed; // 速度計の速度[km/h]
int g_deltaT; // フレーム時間[ms/frame]

ATS_HANDLES g_output; // 出力

CHqn g_hqn; // 阪急新型ATS
