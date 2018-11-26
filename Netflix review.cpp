/*main.cpp*/

//
// Netflix movie review analysis.
//
// John Oshana
// U. of Illinois, Chicago
// CS 341: Fall 2018
// Project 02
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <chrono>

using namespace std;

class Movie{
  private:

  int    movieID, pubYear, numReviews;
  int    ratings[5];
  string movieName;
  double avgRatings;

  public:

Movie(int movieID, string movieName, int pubYear)
  : movieID(movieID), movieName(movieName), pubYear(pubYear)
  {
    numReviews = 0;
    avgRatings = 0;

    for(int i=0; i<5; i++)
      ratings[i] = 0;
  }
//Getters
int getMovieID(){
  return movieID;
}

string getMovieName(){
  return movieName;
}

int getYear(){
  return pubYear;
}

int getNumReviews(){
  return numReviews;
}

int getStars(int x){
  return ratings[x-1];
}

double getAvgRating(){
  return avgRatings;
}
//Setters
void setRatings(int x){
  ratings[x-1]++;
}

//Functions
void totalUpReviews(){
  numReviews++;
}

void calculateAvgRating() {
	double avg = 0;

	for (int i = 0; i < 5; i++)
		avg += ((i + 1) * ratings[i]);

if(getNumReviews()!=0){
	avgRatings = avg / getNumReviews();
}
}
};

class Review{
  private:

  int    reviewID, movieID, userID, rating;
  string reviewDate;

  public:

Review(int reviewID, int movieID, int userID, int rating, string reviewDate)
  : reviewID(reviewID), movieID(movieID), userID(userID), rating(rating), reviewDate(reviewDate)
  {

  }
//Getters
int getMovieID(){
  return movieID;
}

int getUserID(){
  return userID;
}

int getRating(){
  return rating;
}

string getDate(){
  return reviewDate;
}

//Setters
};

// Takes the sorted movie vector and displays the top-ten movies
// along with their ratings
void displayTopTen(std::vector<Movie> m){

  cout << ">> Top-10 Movies <<" << endl;
  cout << endl << "Rank\tID\tReviews\tAvg\tName" << endl;

	for (int i = 0; i < 10; i++)
  cout << i + 1 << ".\t" << m.at(i).getMovieID() << "\t" << m.at(i).getNumReviews() << "\t" << m.at(i).getAvgRating() << "\t" << "\"" << m.at(i).getMovieName() << "\""<< endl;
}

// Allows a user to search for a specific movie or review
// by typing their movie/review ID and will display the information
// of the movie/review
void movieInfo(std::map<int, Movie> movieMap, std::map<int, Review> reviewMap){

  int userInput;

  cout << endl << ">> Movie and Review Information <<" << endl << endl;
  cout << "Please enter a movie ID (< 10,000), a review ID (>= 100,000), 0 to stop> ";
  cin >> userInput;

  while(userInput!=0){
    if(userInput < 0){
      cout << endl << "**invalid id..." << endl;
    }
//movies if...
    if(userInput < 100000){
      auto iter = movieMap.find(userInput);
        if(iter == movieMap.end())
          cout << endl << "movie not found..." << endl;
        else{
          cout << endl << "Movie:\t\t" << "'" << iter->second.getMovieName() << "'" << endl;
          cout << "Year:\t\t" << iter->second.getYear() << endl;
          cout << "Average rating: " << iter->second.getAvgRating() << endl;
          cout << "Num Reviews:\t" << iter->second.getNumReviews() << endl;
          cout << " 1 star: \t" << iter->second.getStars(1) << endl;
          cout << " 2 stars: \t" << iter->second.getStars(2) << endl;
          cout << " 3 stars: \t" << iter->second.getStars(3) << endl;
          cout << " 4 stars: \t" << iter->second.getStars(4) << endl;
          cout << " 5 stars: \t" << iter->second.getStars(5) << endl;
  }
    }
//reviews if...
    if(userInput >= 100000){
      auto iter = reviewMap.find(userInput);
        if(iter == reviewMap.end())
          cout << endl << "review not found..." << endl;
        else{
          auto key = iter->first;
          auto value = iter->second;
          auto movieIter = movieMap.find(iter->second.getMovieID());
          cout << endl << "Movie: " << iter->second.getMovieID() << " (" << movieIter->second.getMovieName() << ")" << endl;
          cout << "Num stars: " << iter->second.getRating() << endl;
          cout << "User ID:   " << iter->second.getUserID() << endl;
          cout << "Date:      " << iter->second.getDate() << endl;
  }
    }
    cout << endl << "Please enter a movie ID (< 10,000), a review ID (>= 100,000), 0 to stop> ";
    cin >> userInput;
  }
}

int main()
{
  std::map<int, Movie> movieMap;
  std::map<int, Review> reviewMap;

  cout << "** Netflix Movie Review Analysis **" << endl;
  cout << endl;

  //
  // input the filenames to process:
  //
  string moviesFN, reviewsFN, line, MovieID, MovieName, PubYear;
  string ReviewID, UserID, Rating, ReviewDate;

  cout << "Enter movie csv file name: ";
  cin >> moviesFN;
  cout << "Enter review csv file name: ";
  cin >> reviewsFN;

  cout << moviesFN << endl;
  cout << reviewsFN << endl;
  cout << endl;

//movies.csv
  ifstream moviefile(moviesFN);
  if(!moviefile.good()){
    cout << "Cannot open the file!" << endl;
    return -1;
  }

  getline(moviefile, line);

  while(getline(moviefile, line)){

    stringstream ss(line);
    getline(ss, MovieID, ',');
    getline(ss, MovieName, ',');
    getline(ss, PubYear);

   Movie m(stoi(MovieID), MovieName, stoi(PubYear));

   movieMap.emplace(stoi(MovieID), m);

}

//reviews.csv
  ifstream reviewfile(reviewsFN);
  if(!reviewfile.good()){
    cout << "Cannot open the file!" << endl;
    return -1;
  }

  getline(reviewfile, line);

  while(getline(reviewfile, line)){

    stringstream ss(line);
    getline(ss, ReviewID, ',');
    getline(ss, MovieID, ',');
    getline(ss, UserID, ',');
    getline(ss, Rating, ',');
    getline(ss, ReviewDate);

   Review r(stoi(ReviewID), stoi(MovieID), stoi(UserID), stoi(Rating), ReviewDate);

   int thisRating = stoi(Rating);
   int thisMovie = stoi(MovieID);

   reviewMap.emplace(stoi(ReviewID), r);

//iterate and total reviews for movies
  auto iter = movieMap.find(thisMovie);
    if(iter == movieMap.end())
      break;
    else{
      iter->second.totalUpReviews();
      iter->second.setRatings(thisRating);
  }
}

//vector for top-10 movies
std::vector<Movie> movieVec;

for(auto& p : movieMap){
  p.second.calculateAvgRating();
  movieVec.push_back(p.second);
}

//sort movies by rating number and if the ratings are equal sort by name
	sort(movieVec.begin(), movieVec.end(),
		[&](Movie m1, Movie m2) {
		if (m1.getAvgRating() > m2.getAvgRating())
			return true;
		else if (m1.getAvgRating() < m2.getAvgRating())
			return false;
		else{
			if (m1.getMovieName() < m2.getMovieName())
				return true;
			else
				return false;
		}
});

  cout << ">> Reading movies... " << movieMap.size() << endl;
  cout << ">> Reading reviews... " << reviewMap.size() << endl << endl;

  displayTopTen(movieVec);
  movieInfo(movieMap, reviewMap);


  //
  // done:
  //
  cout << endl << "** DONE! **" << endl << endl;

  return 0;
}
