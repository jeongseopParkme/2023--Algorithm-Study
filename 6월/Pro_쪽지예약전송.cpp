#include <queue>
#include <cstring>
using namespace std;

#define MAXM	3
#define NONE	0

struct mail
{
	int uID1, uID2, arriveT;
	bool read, cancel1, cancel2;
} mails[100001];

struct box
{
	int time, mID;
	bool operator< (const box& a) const
	{
		if (time == a.time)
			return mID < a.mID;
		return time < a.time;
	}
};

struct user
{
	priority_queue<box> sentbox;
	priority_queue<box> inbox;
} users[1001];

int N;

void init(int N)
{
	::N = N;
	for (int i = 0; i < 1001; i++)
	{
		user& now = users[i];
		while (!now.sentbox.empty()) now.sentbox.pop();
		while (!now.inbox.empty()) now.inbox.pop();
	}
	memset(mails, 0, sizeof(mails));
}

void sendMessage(int cTimestamp, int uID1, int uID2, int mID, int scheduleTimestamp)
{
	mails[mID] = { uID1, uID2, scheduleTimestamp, NONE, NONE, NONE };
	users[uID1].sentbox.push({ cTimestamp, mID });
	users[uID2].inbox.push({ scheduleTimestamp, mID });
}

int retrieveSentbox(int cTimestamp, int uID, int mIDList[MAXM], int uIDList[MAXM], int readList[MAXM])
{
	queue<box> buffer;
	auto& sbox = users[uID].sentbox;
	int ret = 0;

	while (ret < 3 && !sbox.empty())
	{
		box now = sbox.top();
		buffer.push(now);
		sbox.pop();

		if (!mails[now.mID].cancel1)
		{
			mIDList[ret] = now.mID;
			uIDList[ret] = mails[now.mID].uID2;
			readList[ret] = mails[now.mID].read;
			++ret;
		}
	}

	while (!buffer.empty())
	{
		sbox.push(buffer.front());
		buffer.pop();
	}

	return ret;
}

int retrieveInbox(int cTimestamp, int uID, int mIDList[MAXM], int uIDList[MAXM], int readList[MAXM])
{
	queue<box> buffer;
	auto& ibox = users[uID].inbox;
	int ret = 0;

	while (ret < 3 && !ibox.empty())
	{
		box now = ibox.top();
		buffer.push(now);
		ibox.pop();

		if (!mails[now.mID].cancel2 && now.time <= cTimestamp)
		{
			mIDList[ret] = now.mID;
			uIDList[ret] = mails[now.mID].uID1;
			readList[ret] = mails[now.mID].read;
			++ret;
		}
	}

	while (!buffer.empty())
	{
		ibox.push(buffer.front());
		buffer.pop();
	}

	return ret;
}

int readMessage(int cTimestamp, int uID, int mID)
{
	if (!mails[mID].cancel1 && mails[mID].uID1 == uID) //cTimestamp가 항상 증가하므로 취소되지 않았다면 sentbox에 항상 존재
		return 1;
	else if (!mails[mID].cancel2 && mails[mID].uID2 == uID && mails[mID].arriveT <= cTimestamp)
	{
		mails[mID].read = true;
		return 1;
	}
	return 0;
}

int deleteMessage(int cTimestamp, int uID, int mID)
{
	if (!mails[mID].cancel1 && mails[mID].uID1 == uID)
	{
		mails[mID].cancel1 = true;
		if (mails[mID].arriveT > cTimestamp)
			mails[mID].cancel2 = true;
		return 1;
	}
	else if (!mails[mID].cancel2 && mails[mID].uID2 == uID && mails[mID].arriveT <= cTimestamp)
	{
		mails[mID].cancel2 = true;
		return 1;
	}
	return 0;
}