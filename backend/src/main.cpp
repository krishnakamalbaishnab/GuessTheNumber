#include "crow/crow_all.hpp"
#include <random>
#include <unordered_map>

class GameState {
public:
    int targetNumber;
    int attempts;
    
    GameState() : attempts(0) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 100);
        targetNumber = dis(gen);
    }
};

int main() {
    crow::SimpleApp app;
    std::unordered_map<std::string, GameState> games;

    // CORS middleware
    auto& cors = app.get_middleware<crow::CORSHandler>();
    cors
        .global()
        .headers("Content-Type")
        .methods("POST"_method, "GET"_method, "OPTIONS"_method)
        .prefix("/")
        .origin("*");

    // Start new game
    CROW_ROUTE(app, "/new-game")
    .methods("POST"_method)
    ([&games]() {
        std::string gameId = std::to_string(std::rand());
        games[gameId] = GameState();
        return crow::response{crow::json::wvalue({{"gameId", gameId}})};
    });

    // Make a guess
    CROW_ROUTE(app, "/guess")
    .methods("POST"_method)
    ([&games](const crow::request& req) {
        auto body = crow::json::load(req.body);
        std::string gameId = body["gameId"].s();
        int guess = body["guess"].i();

        if (games.find(gameId) == games.end()) {
            return crow::response(400, "Invalid game ID");
        }

        auto& game = games[gameId];
        game.attempts++;

        std::string message;
        bool won = false;

        if (guess > game.targetNumber) {
            message = "Too High! Try again.";
        } else if (guess < game.targetNumber) {
            message = "Too Low! Try again.";
        } else {
            message = "Congratulations! You won in " + std::to_string(game.attempts) + " attempts!";
            won = true;
        }

        return crow::response{crow::json::wvalue({
            {"message", message},
            {"attempts", game.attempts},
            {"won", won}
        })};
    });

    app.port(3000).run();
    return 0;
} 