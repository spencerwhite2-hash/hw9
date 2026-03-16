#include <iostream>
#include <cmath>
using namespace std;

void display(double arr[], int size) { // This function takes an array of doubles and its size as parameters and displays the elements of the array in a formatted manner
	for (int i = 0; i < size; i++) { // Loop through each element in the array to display its value
		cout << "[" << arr[i] << "]" << " "; // Print each element of the array enclosed in square brackets followed by a space for better readability
	}
	cout << endl;
}

double mean(double arr[], int size) { // The mean is calculated by summing all the values in the dataset and then dividing by the number of values
	double sum = 0.0; // Initialize a variable to store the sum of the values in the dataset
	for (int i = 0; i < size; i++) { // Loop through each element in the array to calculate the sum of the values in the dataset
		sum += arr[i]; // Add each value in the dataset to the sum variable
	}
	return sum / size; // Return the mean by dividing the sum of the values by the number of values in the dataset
}

double median(double arr[], int size) {   // The median is calculated by first sorting the dataset and then finding the middle value(s)
	if (size % 2 == 0) {                  // If the size of the dataset is even, the median is calculated by taking the average of the two middle values in the sorted array
		return (arr[size / 2 - 1] + arr[size / 2]) / 2.0; // If the size of the dataset is even, the median is calculated by taking the average of the two middle values in the sorted array
	}
	else {
		return arr[size / 2]; // If the size of the dataset is odd, the median is the middle value in the sorted array, which is located at index size / 2
	}
}

double variance(double arr[], int size) { // The variance is calculated by finding the mean and then summing the squared differences from the mean
	double m = mean(arr, size);
	double sum = 0.0; 

	for (int i = 0; i < size; i++) {  // Loop through each element in the array to calculate the variance
		sum += (arr[i] - m) * (arr[i] - m); // The variance is calculated by summing the squared differences from the mean
	}

	return sum / (size - 1); // Sample variance is calculated by dividing by (size - 1) to account for the degrees of freedom in the dataset
}

double standardDeviation(double arr[], int size) { // The standard deviation is the square root of the variance
	return sqrt(variance(arr, size)); // The standard deviation is the square root of the variance
}

double range(double arr[], int size) { // The range is the difference between the maximum and minimum values in the dataset
	return arr[size - 1] - arr[0]; // Since the array is sorted, the range is the difference between the last and first elements
}

void sortArray(double arr[], int size) // Selection sort algorithm
{
	for (int i = 0; i < size - 1; i++) // Loop through each element in the array except the last one
	{
		int minIndex = i; // Assume the minimum element is the first element of the unsorted part

		for (int j = i + 1; j < size; j++) // Loop through the unsorted elements
		{
			if (arr[j] < arr[minIndex]) // Compare the current element with the minimum element
			{
				minIndex = j; // Update the index of the minimum element
			}
		}

		double temp = arr[i]; // Swap the elements
		arr[i] = arr[minIndex]; // Swap the elements
		arr[minIndex] = temp; // Swap the elements
	}
}

void mode(double arr[], int size) // The mode is the value that appears most frequently in the dataset
{
	double modeArr[2][100]; // modeArr[0] will store the unique values, and modeArr[1] will store their corresponding counts
	int filled = 0; // This variable keeps track of how many unique values have been stored in modeArr

	for (int i = 0; i < size; i++) // Loop through each element in the input array to count the frequency of each unique value
	{
		bool found = false; // This variable is used to check if the current value has already been counted

		for (int j = 0; j < filled; j++) // Loop through the filled portion of modeArr to check if the current value has already been counted
		{
			if (modeArr[0][j] == arr[i]) // If the current value is found in modeArr, increment its count
			{
				modeArr[1][j]++; // Increment the count for the existing value
				found = true; // Set found to true to indicate that the value has been counted
				break; 
			}
		}

		if (!found) // If the current value is not found in modeArr, add it as a new unique value with a count of 1
		{
			modeArr[0][filled] = arr[i]; // Store the unique value in modeArr[0]
			modeArr[1][filled] = 1; // Initialize the count for the new unique value to 1
			filled++; // Increment the filled variable to indicate that a new unique value has been added to modeArr
		}
	}

	int maxCount = 0; // This variable will store the maximum count of occurrences for any value in the dataset

	for (int i = 0; i < filled; i++) // Loop through the filled portion of modeArr to find the maximum count of occurrences for any value in the dataset
	{
		if (modeArr[1][i] > maxCount) // If the count for the current value is greater than the current maxCount, update maxCount
		{
			maxCount = modeArr[1][i]; // Update maxCount to the new maximum count
		}
	}

	if (maxCount == 1) // If maxCount is 1, it means that all values in the dataset are unique and there is no mode
	{
		cout << "Mode: None" << endl;
		return;
	}

	cout << "Mode: ";

	for (int i = 0; i < filled; i++) // Loop through the filled portion of modeArr to find all values that have a count equal to maxCount, which are the modes of the dataset
	{
		if (modeArr[1][i] == maxCount) // If the count for the current value is equal to maxCount, it means that this value is a mode of the dataset
		{
			cout << modeArr[0][i] << " "; // Print the mode value followed by a space
		}
	}

	cout << endl;
}

int main() {

	int size;
	cout << "Descriptive Statistics Calculator" << endl;
	cout << "Number of items in dataset: ";
	cin >> size;

	double* dataset = new double[size];  // Dynamically allocate an array to store the dataset based on the size provided by the user

	for (int i = 0; i < size; i++)	//   Loop through each index from 0 to size-1 to read the data points for the dataset from the user
	{
		cout << "Enter data point (Leave blank to stop): " << i + 1 << ": "; // Prompt the user to enter each data point for the dataset, indicating the current index for clarity
		cin >> dataset[i]; // Read each data point from the user and store it in the dataset array for later calculations
	}

	cout << endl;
	cout << "Original dataset: ";
	display(dataset, size); // Display the original dataset entered by the user to confirm the input before performing any calculations

	double* copy = new double[size]; // Create a copy of the original dataset to preserve the original order for later calculations

	for (int i = 0; i < size; i++) // Loop through each element in the original dataset to create a copy of it for sorting and calculations
	{
		copy[i] = dataset[i]; // Copy the original dataset into the copy array to preserve the original order for later calculations
	}


	sortArray(copy, size);

	cout << "Sorted copy: ";
	display(copy, size);
	cout << endl;

	cout << "CENTRAL TENDENCY" << endl;
	cout << "Mean: " << mean(dataset, size) << endl;
	cout << "Median: " << median(copy, size) << endl;
	mode(dataset, size);
	cout << endl;

	cout << "DISPERSION" << endl;
	cout << "Range: " << range(copy, size) << endl;
	cout << "Variance: " << variance(dataset, size) << endl;
	cout << "Standard deviation: " << standardDeviation(dataset, size) << endl;

	delete[] dataset; // Deallocate the memory allocated for the dataset array
	delete[] copy; // Deallocate the memory allocated for the copy array
}