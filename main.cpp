#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

std::vector<double> distancebetweencircles(std::vector<std::vector<double>> points, int n){
    std::vector<double> dist1;
    for (int i = 0; i < n + 1; i++) {
        for (int j = 1; j < 2; j++) {
            for (int u = 1; u < n + 1; u++) {
                dist1.push_back(sqrt((points[i][j] - points[i+u][j])*(points[i][j] - points[i+u][j]) +
                     (points[i][j+1] - points[i+u][j+1])*(points[i][j+1] - points[i+u][j+1])));
            }
        }
    }
    return dist1;
}

std::vector<double> distancefromobserver(std::vector<std::vector<double>> points, int n){
    std::vector<double> dist2;
        for (int j = 1; j < 2; j++) {
            for (int u = 1; u < n + 1; u++) {
                dist2.push_back(sqrt((points[0][j] - points[0+u][j])*(points[0][j] - points[0+u][j]) +
                     (points[0][j+1] - points[0+u][j+1])*(points[0][j+1] - points[0+u][j+1])));
            }
        }
    return dist2;
}

std::vector<std::vector<double>> degrees(std::vector<std::vector<double>> points, std::vector<double> dist2, int n){
    std::vector<std::vector<double>> deg (n, std::vector<double>(2, 0.0));
    for (int i = 0; i < n; i++) {
        if (points[i+1][0] >= std::abs(points[i+1][2]) and points[i+1][1] > 0){
            deg[i][0] = (std::asin(points[i+1][2]/dist2[i])*180/M_PI - std::asin(points[i+1][0]/dist2[i])*180/M_PI);
            deg[i][1] = (std::asin(points[i+1][2]/dist2[i])*180/M_PI + std::asin(points[i+1][0]/dist2[i])*180/M_PI);
        } else if (points[i+1][0] < points[i+1][2] and points[i+1][1] > 0 and points[i+1][2] > 0){
            deg[i][0] = (std::asin(points[i+1][2]/dist2[i])*180/M_PI - std::asin(points[i+1][0]/dist2[i])*180/M_PI);
            deg[i][1] = (std::asin(points[i+1][2]/dist2[i])*180/M_PI + std::asin(points[i+1][0]/dist2[i])*180/M_PI);
        } else if (points[i+1][0] >= std::abs(points[i+1][1]) and points[i+1][2] > 0){
            deg[i][0] = 180 - (std::asin(points[i+1][2]/dist2[i])*180/M_PI + std::asin(points[i+1][0]/dist2[i])*180/M_PI);
            deg[i][1] = 180 - (std::asin(points[i+1][2]/dist2[i])*180/M_PI - std::asin(points[i+1][0]/dist2[i])*180/M_PI);
        } else if (points[i+1][0] < std::abs(points[i+1][1]) and points[i+1][1] < 0 and points[i+1][2] > 0){
            deg[i][0] = 180 - (std::asin(points[i+1][2]/dist2[i])*180/M_PI + std::asin(points[i+1][0]/dist2[i])*180/M_PI);
            deg[i][1] = 180 - (std::asin(points[i+1][2]/dist2[i])*180/M_PI - std::asin(points[i+1][0]/dist2[i])*180/M_PI);
        } else if (points[i+1][0] >= std::abs(points[i+1][2]) and points[i+1][1] < 0){
            deg[i][0] = 180 - std::abs(std::asin(points[i+1][2]/dist2[i])*180/M_PI + std::asin(points[i+1][0]/dist2[i])*180/M_PI);
            deg[i][1] = 180 + std::abs(std::asin(points[i+1][2]/dist2[i])*180/M_PI - std::asin(points[i+1][0]/dist2[i])*180/M_PI);
        } else if (points[i+1][0] < std::abs(points[i+1][2]) and points[i+1][1] < 0 and points[i+1][2] < 0){
            deg[i][0] = 180 + std::abs(std::asin(points[i+1][2]/dist2[i])*180/M_PI + std::asin(points[i+1][0]/dist2[i])*180/M_PI);
            deg[i][1] = 180 + std::abs(std::asin(points[i+1][2]/dist2[i])*180/M_PI - std::asin(points[i+1][0]/dist2[i])*180/M_PI);
        } else if (points[i+1][0] >= std::abs(points[i+1][1]) and points[i+1][2] < 0){
            deg[i][0] = 360 - std::abs(std::asin(points[i+1][2]/dist2[i])*180/M_PI - std::asin(points[i+1][0]/dist2[i])*180/M_PI);
            deg[i][1] = 360 - std::abs(std::asin(points[i+1][2]/dist2[i])*180/M_PI + std::asin(points[i+1][0]/dist2[i])*180/M_PI);
        } else if (points[i+1][0] < points[i+1][1] and points[i+1][1] > 0 and points[i+1][2] < 0){
            deg[i][0] = 360 - std::abs(std::asin(points[i+1][2]/dist2[i])*180/M_PI - std::asin(points[i+1][0]/dist2[i])*180/M_PI);
            deg[i][1] = 360 - std::abs(std::asin(points[i+1][2]/dist2[i])*180/M_PI + std::asin(points[i+1][0]/dist2[i])*180/M_PI);
        }
        }
    return deg;
}

std::vector<std::vector<double>> customsort(std::vector<std::vector<double>>& deg, int e){
    for (int i = 0; i < deg.size() - 1; i++){
        for (int j = 0; j < deg.size() - i - 1; j++){
            if (deg[j][e] > deg[j+1][e]){
                std::swap(deg[j], deg[j+1]);
            }
        }
    }
    return deg;
}

int obscured_circles(std::vector<double>sumradiuses,std::vector<double>dist1,std::vector<std::vector<double>>distdegsortedbydistance,std::vector<std::vector<std::vector<double>>>relativecircles1,int n){
    int a = 0;
    int b = 0;
    std::vector<double> track = {0.0,0.0,0.0};
    std::vector<std::vector<double>> bottle = distdegsortedbydistance;
    
    for (int j = 0; j < dist1.size(); j++) {
        if (sumradiuses[j] > dist1[j]){
            a++;
        }
    }
    if (a > 0) {
        std::cout << "intersection between circles or observer and circles, choose another radiuses/coordinates" << '\n';
    }
    else {
        std::cout << "amount of obscured circles is:" << '\n';
    }
        
        for (int p = 0; p < n - 1; p++){
            for (int e = 1; e < n; e++){
                if (distdegsortedbydistance[p][1] <= distdegsortedbydistance[e][1] and distdegsortedbydistance[p][2] >= distdegsortedbydistance[e][2] and p < e){
                    bottle[e] = track;
                }
            }
        }
            
        for (int p = 2; p < distdegsortedbydistance.size(); p++){
            for (int e = 0; e < relativecircles1.size(); e++){
                if (distdegsortedbydistance[p][1] >= relativecircles1[e][0][1] and distdegsortedbydistance[p][2] <= relativecircles1[e][relativecircles1[e].size()-1][2] and distdegsortedbydistance[p][0] > relativecircles1[e][0][0] and distdegsortedbydistance[p][0] > relativecircles1[e][relativecircles1[e].size()-1][0]){
                    bottle[p] = track;
                }
            }
        }
    
    std::erase(bottle, track);
    b = n - bottle.size();
    return b;
}

int main() {
    int n;
    std::cout << "print number of circles " << '\n';
    std::cin >> n;
    std::vector<std::vector<double>> circles (n + 1, std::vector<double>(3, 0.0));
    std::cout << "print each circle: radius, x coordinate, y coordinate" << '\n';
    for (int i = 1; i < n + 1; i++) {
        for (double j = 0; j < 3; j++) {
            std::cin >> circles[i][j];
        }
    }
    
    std::vector<std::vector<double>> circles2 = circles;
    for (int i = 0; i < n + 1; i++) {
        circles2.push_back(circles[i]);
    }
    
    std::vector<double> radiuses;
    for (double i = 0; i < n + 1; i++) {
        radiuses.push_back(circles2[i][0]);
    }
    for (double i = 0; i < n + 1; i++) {
        radiuses.push_back(radiuses[i]);
    }
    
    std::vector<double> sumradiuses;
    for (double p = 0; p < radiuses.size()/2; p++){
        for (double s = 1; s < radiuses.size()/2; s++){
            sumradiuses.push_back(radiuses[p] + radiuses[p+s]);
        }
    }
    
    std::vector<double> dist1 = distancebetweencircles(circles2, n);
    
    std::vector<double> dist2 = distancefromobserver(circles, n);
    
    std::vector<std::vector<double>> distdeg = degrees(circles, dist2, n);
    
    for (int i = 0; i < n; i++){
        distdeg[i].insert(distdeg[i].begin(), dist2[i]);
    }
    
    std::vector<std::vector<double>> distdegsortedbydistance = customsort(distdeg, 0);
    
    std::vector<std::vector<double>> distdegsortedbyhighdegree = customsort(distdeg, 2);
    
    std::vector<std::vector<std::vector<std::vector<double>>>>
    hardcasecircles4d(n-1,std::vector<std::vector<std::vector<double>>>(n-1,std::vector<std::vector<double>>(0,std::vector<double>(0, 0))));
    
    std::vector<std::vector<std::vector<double>>> hardcasecircles3d(0,std::vector<std::vector<double>>(0,std::vector<double>(0, 0)));
    
    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < n - 1 - i; j++){
            hardcasecircles4d[i][j] = distdegsortedbyhighdegree;
        }
    }
    
    for (int i = 1; i < n - 1; i++){
        for (int j = 0; j < n - 1 - i; j++){
            hardcasecircles4d[i][j].erase(hardcasecircles4d[i][j].begin(), hardcasecircles4d[i][j].begin() + i);
        }
    }
    
    for (int i = 0; i < n - 2; i++){
        for (int j = 1; j < n - 1 - i; j++){
            hardcasecircles4d[i][j].erase(hardcasecircles4d[i][j].begin() + 1, hardcasecircles4d[i][j].begin() + 1 + j);
        }
    }
    
    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < n - 1 - i; j++){
            hardcasecircles3d.push_back(hardcasecircles4d[i][j]);
        }
    }
    
    std::vector<std::vector<std::vector<double>>> relativecircles1(hardcasecircles3d.size(),std::vector<std::vector<double>>(0,std::vector<double>(0, 0)));
    std::vector<std::vector<std::vector<double>>> relativecircles2(hardcasecircles3d.size(),std::vector<std::vector<double>>(0,std::vector<double>(0, 0)));
    
    for (int u = 0; u < hardcasecircles3d.size(); u++){
        for (int i = 0; i < 1; i++){
            for (int j = 0; j < hardcasecircles3d[u].size() - 1; j++){
                if (hardcasecircles3d[u][i+j][1] < hardcasecircles3d[u][i+j+1][1] and hardcasecircles3d[u][i+j][2] < hardcasecircles3d[u][i+j+1][2] and hardcasecircles3d[u][i+j][2] >= hardcasecircles3d[u][i+j+1][1]){
                    relativecircles1[u].push_back(hardcasecircles3d[u][i+j]);
                }
                else{
                    break;
                }
            }
        }
    }
    
    for (int u = 0; u < hardcasecircles3d.size(); u++){
        for (int i = 0; i < 1; i++){
            for (int j = 0; j < hardcasecircles3d[u].size() - 1; j++){
                if (hardcasecircles3d[u][i+j][1] < hardcasecircles3d[u][i+j+1][1] and hardcasecircles3d[u][i+j][2] < hardcasecircles3d[u][i+j+1][2] and hardcasecircles3d[u][i+j][2] >= hardcasecircles3d[u][i+j+1][1]){
                    relativecircles2[u].push_back(hardcasecircles3d[u][i+j+1]);
                }
                else{
                    break;
                }
            }
        }
    }
    
    for (int i = 0; i < relativecircles1.size(); i++){
        if (!relativecircles2[i].empty()){
            auto last_element = relativecircles2[i].back();
            relativecircles1[i].push_back(last_element);
        }
    }
    
    relativecircles1.erase(std::remove_if(relativecircles1.begin(), relativecircles1.end(),
                                          [](const std::vector<std::vector<double>>& vec2D) {
        return vec2D.empty();}),
                           relativecircles1.end());
    
    int w = obscured_circles(sumradiuses, dist1, distdegsortedbydistance, relativecircles1, n);
    
    std::cout << w << '\n';
}
