#define MAX_N				20000
#define MAX_M				128
#define MAX_BLOCKCOUNT		1250
#define MAX_DATALENGTH		5120000
#define FRAMESIZE			256

struct huffman
{
	int symbol, codeword, codewordLength;
};

struct Node
{
	int symbol;
	Node* left, * right;
	Node() : symbol(0), left(nullptr), right(nullptr)
	{

	}
} *root;

typedef unsigned int uint;
typedef unsigned char uchar;

constexpr uint maxFrames = 20000;
constexpr uint pixelsPerFrame = 16 * 16;
constexpr uint framesPerBlock = 16;
constexpr uint maxBlocks = maxFrames / framesPerBlock;
constexpr uint pixelsPerBlock = pixelsPerFrame * framesPerBlock;

uchar dib[maxBlocks][pixelsPerBlock]; // Difference Image Block
uchar vd[maxFrames][pixelsPerFrame]; // Video Data
uint frame, N;

void deleteNode(Node* now)
{
	if (now->left != nullptr)
		deleteNode(now->left);
	if (now->right != nullptr)
		deleteNode(now->right);
	delete now;
}

void Init(int N, int* size, unsigned char* data, int M, struct huffman* code)
{
	::N = N;
	// make huffman tree 
	root = new Node;
	for (int idx = 0; idx < M; idx++)
	{
		Node *now = root;
		for (int i = 1; i <= code[idx].codewordLength; i++)
		{
			uint bit = (code[idx].codeword >> (code[idx].codewordLength - i)) & 1;
			if (bit == 0)
			{
				if (now->left == nullptr)
					now->left = new Node;
				now = now->left;
			}
			else
			{
				if (now->right == nullptr)
					now->right = new Node;
				now = now->right;
			}
		}
		now->symbol = code[idx].symbol;
	}
	// Decode 'data' to 'Difference Image Block' 
	uint totalBlock = N / framesPerBlock;
	uint startIdx = 0;
	for (uint block = 0; block < totalBlock; block++)
	{
		startIdx += block == 0 ? 0 : size[block - 1];
		uint bitIdx = 0;
		for (int pixel = 0; pixel < pixelsPerBlock; pixel++)
		{
			Node* now = root;
			while (now->left != nullptr || now->right != nullptr)
			{
				uchar bit = (data[startIdx + bitIdx / 8] >> (7 - bitIdx % 8)) & 1;
				if (bit == 0)
					now = now->left;
				else
					now = now->right;
				++bitIdx;
			}
			dib[block][pixel] = now->symbol;
		}
	}
	// Decode 'Difference Image Block' to 'Video Data'
	for (int frame = 0; frame < N; frame++)
	{
		if (frame % framesPerBlock == 0)
		{
			uint block = frame / framesPerBlock;
			for (int pixel = 0; pixel < pixelsPerFrame; pixel++)
			{
				vd[frame][pixel] = dib[block][pixel];
			}
		}
		else
		{
			uint block = frame / framesPerBlock;
			uint pixelBase = frame % framesPerBlock * pixelsPerFrame;
			for (int pixel = 0; pixel < pixelsPerFrame; pixel++)
			{
				vd[frame][pixel] = dib[block][pixelBase + pixel] + vd[frame - 1][pixel] - 128;
			}
		}
	}
	// delete huffman tree
	deleteNode(root);
}

void Goto(int frame)
{
	::frame = frame;
}

int Tick(unsigned char* screen)
{
	for (int pixel = 0; pixel < pixelsPerFrame; pixel++)
		screen[pixel] = vd[frame][pixel];
	return frame < N - 1 ? frame++ : frame;
}