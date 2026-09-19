class Solution {
public:
    bool checkOverlap(int radius, int xCenter, int yCenter,
                      int x1, int y1, int x2, int y2) {

        // Closest x-coordinate on the rectangle
        int closestX = max(x1, min(xCenter, x2));

        // Closest y-coordinate on the rectangle
        int closestY = max(y1, min(yCenter, y2));

        // Squared distance from circle center to closest point
        long long dx = xCenter - closestX;
        long long dy = yCenter - closestY;

        long long distanceSquared = dx * dx + dy * dy;

        return distanceSquared <= 1LL * radius * radius;
    }
};