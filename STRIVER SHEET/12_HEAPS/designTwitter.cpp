#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
Problem Title: Design Twitter
Problem Link: https://leetcode.com/problems/design-twitter

Problem Statement:
Design a simplified version of Twitter where users can post tweets,
follow/unfollow other users, and retrieve the 10 most recent tweets
in their news feed. The news feed should include tweets from the user
and those they follow, ranked from most recent to least recent.

Example:
Input:
postTweet(1, 5);
getNewsFeed(1); // returns [5]
follow(1, 2);
postTweet(2, 6);
getNewsFeed(1); // returns [6, 5]
unfollow(1, 2);
getNewsFeed(1); // returns [5]

=========================================================
*/

/* ------------------------------------------------------
   Approach: Use HashMaps and Min-Heap for News Feed
   ------------------------------------------------------
   💡 Idea:
   - Maintain tweet lists per user with timestamps.
   - Track follow relationships with sets.
   - For news feed, merge tweets of user and their followees efficiently using a min-heap.

   🧩 Algorithm:
   1. Store tweets (timestamp, tweetId) in a vector per user.
   2. Maintain followees in an unordered_set (follow self by default).
   3. On getNewsFeed:
      - Iterate followees, push tweets into a min-heap capped at size 10 by timestamp.
   4. Return tweets ordered from most recent to least recent.

   ⏱ Time Complexity:
   - postTweet: O(1)
   - getNewsFeed: O(F * T log 10), F=followees, T=tweets per followee (usually small needed)
   - follow/unfollow: O(1)

   📦 Space Complexity: O(U + T) for users and tweets
------------------------------------------------------ */
class Twitter {
    unordered_map<int, vector<pair<int, int>>> tweets; // user -> {time, tweetId}
    unordered_map<int, unordered_set<int>> following;  // user -> followees
    int timeStamp;

public:
    Twitter() {
        timeStamp = 1;
    }

    void postTweet(int userId, int tweetId) {
        tweets[userId].push_back({timeStamp, tweetId});
        following[userId].insert(userId);  // follow self
        timeStamp++;
    }

    vector<int> getNewsFeed(int userId) {
        // Min-heap based on timestamps (smallest at top)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        for (int followee : following[userId]) {
            for (auto& tweet : tweets[followee]) {
                pq.push(tweet);
                if (pq.size() > 10) pq.pop();  // keep only top 10 latest
            }
        }

        vector<int> result;
        while (!pq.empty()) {
            result.push_back(pq.top().second);
            pq.pop();
        }
        reverse(result.begin(), result.end());
        return result;
    }

    void follow(int followerId, int followeeId) {
        following[followerId].insert(followerId); // ensure self-follow
        following[followerId].insert(followeeId);
        following[followeeId].insert(followeeId); // ensure followee self-follow
    }

    void unfollow(int followerId, int followeeId) {
        if (followerId == followeeId) return; // cannot unfollow self
        following[followerId].erase(followeeId);
    }
};

/* ===================== Main Function ===================== */
int main() {
    Twitter twitter;

    twitter.postTweet(1, 5);
    vector<int> feed1 = twitter.getNewsFeed(1);
    cout << "News Feed for User 1: ";
    for (int id : feed1) cout << id << " ";
    cout << endl;

    twitter.follow(1, 2);
    twitter.postTweet(2, 6);
    vector<int> feed2 = twitter.getNewsFeed(1);
    cout << "News Feed for User 1 after following User 2: ";
    for (int id : feed2) cout << id << " ";
    cout << endl;

    twitter.unfollow(1, 2);
    vector<int> feed3 = twitter.getNewsFeed(1);
    cout << "News Feed for User 1 after unfollowing User 2: ";
    for (int id : feed3) cout << id << " ";
    cout << endl;

    /* ------------------------------------------------------
       ✅ Approach Overview
       ------------------------------------------------------
       | Method              | Time Complexity       | Space Complexity | Notes                    |
       |---------------------|----------------------|-------------------|--------------------------|
       | Using HashMaps + Heap| getNewsFeed O(F*T log10)| O(U + T)      | Practical for scenarios  |
       ------------------------------------------------------
    ------------------------------------------------------ */
    return 0;
}
