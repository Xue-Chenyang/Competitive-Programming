import java.util.*;

public class Solution {

    static class Vector {
        double x;
        double y;
        double z;

        public Vector(double x, double y, double z) {
            this.x = x;
            this.y = y;
            this.z = z;
        }

        public static boolean isInSync(Vector v1, Vector v2) {
            if (v1.x != 0) {
                return v2.x / v1.x > 0;
            }
            if (v1.y != 0) {
                return v2.y / v1.y > 0;
            }
            return v2.z / v1.z > 0;
        }

        public static Vector crossProduct(Vector v1, Vector v2) {
            return new Vector(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
        }

        public static double dotProduct(Vector v) {
            return dotProduct(v, v);
        }

        public static double dotProduct(Vector v1, Vector v2) {
            return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
        }

        public static Vector multiply(Vector v, double multiplier) {
            return new Vector(v.x * multiplier, v.y * multiplier, v.z * multiplier);
        }

        public static Vector getProjection(Vector line, Vector toBeProjected) {
            double multiplier = dotProduct(line, toBeProjected) / dotProduct(line);
            return multiply(line, multiplier);
        }
    }

    static class Point{
        double x;
        double y;
        double z;

        public Point(double x, double y, double z) {
            this.x = x;
            this.y = y;
            this.z = z;
        }

        public static Vector getVector(Point p1, Point p2) {
            return new Vector(p2.x - p1.x, p2.y - p1.y, p2.z - p1.z);
        }
    }

    static class Polygon {
        int verticeCount;
        ArrayList<Point> vertices;

        public Polygon(int verticeCount, ArrayList<Point> vertices) {
            this.verticeCount = verticeCount;
            this.vertices = vertices;
        }

        public Point getInternalPoint() {
            Point p1 = mid_point(vertices.get(0), vertices.get(1));
            Point p2 = mid_point(vertices.get(1), vertices.get(2));
            return mid_point(p1, p2);
        }

        public void setDirection(boolean b) {
            if (!b) {
                Collections.reverse(vertices);
            }
        }

        public Vector getNormalVector() {
            Vector v1 = Point.getVector(vertices.get(1), vertices.get(2));
            Vector v2 = Point.getVector(vertices.get(1), vertices.get(0));
            return Vector.crossProduct(v1, v2);
        }

        public Vector getPerpendicularVector(Point pointOfInterest) {
            Vector normal = this.getNormalVector();
            return Vector.getProjection(normal, Point.getVector(vertices.get(0), pointOfInterest));
        }
    }

    static Point mid_point(Point p1, Point p2) {
        return new Point((p1.x + p2.x) / 2, (p1.y + p2.y) / 2, (p1.z + p2.z) / 2);
    }

    static Point findPointInSolid(ArrayList<Polygon> sides) {
        Polygon firstSide = sides.get(0);
        Polygon secondSide = sides.get(1);
        Point point1 = firstSide.getInternalPoint();
        Point point2 = secondSide.getInternalPoint();
        return mid_point(point1, point2);
    }

    static void determineSignOfSide(ArrayList<Polygon> sides, Point pointInSolid) {
        for (Polygon side : sides) {
            Vector normalVector = side.getNormalVector();
            Vector perpendicularVector = side.getPerpendicularVector(pointInSolid);
            side.setDirection(Vector.isInSync(normalVector, perpendicularVector));
        }
    }

    static double getDeterminant(Point p1, Point p2, Point p3) {
        return (p1.x * (p2.y * p3.z - p2.z * p3.y) - p1.y * (p2.x * p3.z - p2.z * p3.x) + p1.z * (p2.x * p3.y - p2.y * p3.x));
    }

    static double calculateVolume(Polygon polygon) {
        int fixed = 0;
        int left = 1;
        int right = 2;
        double sum = 0;
        while (right < polygon.vertices.size()) {
            sum += getDeterminant(polygon.vertices.get(fixed), polygon.vertices.get(left), polygon.vertices.get(right)) / 6;
            left ++;
            right ++;
        }
        return sum;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int polyhedraCount = Integer.parseInt(scanner.nextLine());
        double total_volume = 0;
        for (int i = 0; i < polyhedraCount; i ++) {
            int polygonCount = Integer.parseInt(scanner.nextLine());
            ArrayList<Polygon> sides = new ArrayList<>();
            // Record all sides
            for (int j = 0; j < polygonCount; j ++) {
                ArrayList<Point> vertices = new ArrayList<>();
                String[] data = scanner.nextLine().split(" ");
                for (int k = 0; k < Integer.parseInt(data[0]); k ++) {
                    Point newPoint = new Point(Double.parseDouble(data[k * 3 + 1]), Double.parseDouble(data[k * 3 + 2]), Double.parseDouble(data[k * 3 + 3]));
                    vertices.add(newPoint);
                }
                sides.add(new Polygon(Integer.parseInt(data[0]), vertices));
            }
            // Find a point in the solid
            Point pointInSolid = findPointInSolid(sides);
            // Determine sign of each side
            determineSignOfSide(sides, pointInSolid);
            // Calculate signed volume of each tetrahedra
            double volume = 0;
            Point ref = new Point(0, 0, 0);
            for (Polygon polygon : sides) {
                volume += calculateVolume(polygon);
            }
            total_volume += volume;
        }
        System.out.println(String.format("%.2f",total_volume * -1));
    }
}
