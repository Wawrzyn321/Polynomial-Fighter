#ifndef DESIGNATED_TARGET_H
#define DESIGNATED_TARGET_H

struct DesignatedTarget
{
	unsigned recipientID;
	int root;

	bool operator==(const DesignatedTarget &other) const
	{
		return other.recipientID == recipientID && other.root == root;
	}
};

#endif