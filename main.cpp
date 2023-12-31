#include <cstdlib>
#include "include/urlencoder.h"
#include <curl/curl.h>
#include <iomanip>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

// getting env variables
const char *token = std::getenv("TOKEN"); // telegram bot token
const char *cid = std::getenv("CID");     // telegram group/chat id

// telegram's base url where we send requests from the bot
const char *baseUrl = "https://api.telegram.org/bot";

size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char *>(contents), totalSize);
    return totalSize;
}

// Function to send a message to the Telegram API
void sendTelegramMessage(const std::string &chatId, const std::string &text) {
    CURL *curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Error initializing libcurl." << std::endl;
        return;
    }

    if (!token || !cid) {
        std::cerr << "TOKEN or CID environment variable not set." << std::endl;
        curl_easy_cleanup(curl);
        return;
    }

    // Use the urlEncode function from the header file
    std::string url = baseUrl + std::string(token) + "/sendMessage";
    url += "?chat_id=" + chatId + "&text=" + urlEncode(text);

    std::cout << "Request URL: " << url << std::endl;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    // Perform the HTTP GET request
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "Failed to perform HTTP request: " << curl_easy_strerror(res)
                  << std::endl;
    }

    curl_easy_cleanup(curl);
}

// Function to check if the message contains the "/hi" command
bool isHiCommand(const std::string &message) {
    return message.find("/hi") != std::string::npos;
}

// Function to simulate incoming messages
std::string simulateIncomingMessage() {
    // Simulate receiving a message
    // In a real bot, you would use the Telegram Bot API's "getUpdates" method
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate a delay
    return "/hi";
}

// Function to process incoming messages
void processIncomingMessages() {
    // Simulate receiving a message
    std::string incomingMessage = simulateIncomingMessage();

    // Check if the message contains the "/hi" command
    if (isHiCommand(incomingMessage)) {
        // Respond with "Hello!" when "/hi" is received
        sendTelegramMessage(cid, "Hello!");
    }
}

int main() {
    if (!token) {
        std::cerr << "TOKEN environment variable not set." << std::endl;
        return 1;
    } else {
        std::cout << "Bot token: " << token << std::endl;
    }

    if (!cid) {
        std::cerr << "CID environment variable not set." << std::endl;
        return 1;
    } else {
        std::cout << "Chat ID: " << cid << std::endl;
    }

    // Continuous loop to poll for incoming messages
    while (true) {
        processIncomingMessages();
        // TODO: Add a delay here to avoid excessive API calls (e.g., sleep for a few seconds)
    }

    return 0;
}
