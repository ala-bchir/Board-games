
TARGET = jeu

TEST_TARGET = test

# Compilateur
CC = g++

# Dossiers
CMP_DIR = component
SRC_DIR = src
INC_DIR = include

# Options de compilation
CFLAGS = -Wall -std=c++11 -I$(INC_DIR) 


# Drapeaux de liaison pour SFML
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system


# Fichiers source
SRC = $(SRC_DIR)/main.cpp $(SRC_DIR)/$(CMP_DIR)/Jeu.cpp $(SRC_DIR)/Butin.cpp $(SRC_DIR)/$(CMP_DIR)/Damier.cpp $(SRC_DIR)/$(CMP_DIR)/Pion.cpp


TEST_SRC = $(SRC_DIR)/test.cpp $(SRC_DIR)/$(CMP_DIR)/Joueur.cpp $(SRC_DIR)/$(CMP_DIR)/Pion.cpp

# Règle par défaut
all: $(TARGET)

# Règle de compilation
$(TARGET): $(SRC)
	$(CC) $(CFLAGS)  $(SRC) -o $(TARGET)  $(SFML_FLAGS)

# Règle pour le test
test: $(TEST_SRC)
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(TEST_TARGET) $(SFML_FLAGS)

# Règle de nettoyage
clean:
	rm -f $(TARGET) $(TEST_TARGET)
