import random
import json
import sys


def load_players_from_json(file_path):
    """Load players and tiers from a JSON file."""
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            data = json.load(f)
        
        # Convert string keys to integers for tier levels
        tiers = {}
        for tier_str, players in data['tiers'].items():
            tiers[int(tier_str)] = players.copy()  # Create a copy to avoid modifying original data
        
        return tiers
    except FileNotFoundError:
        print(f"Error: File '{file_path}' not found.")
        sys.exit(1)
    except json.JSONDecodeError:
        print(f"Error: Invalid JSON format in '{file_path}'.")
        sys.exit(1)
    except KeyError:
        print("Error: JSON file must contain a 'tiers' key with tier data.")
        sys.exit(1)


def print_player_summary(tiers):
    """Print summary of total players."""
    total_players = len([x for tier in tiers.values() for x in tier])
    print(f"Total players: {total_players}")


def draft(tiers):
    """Draft a player from the highest available tier."""
    for i in sorted(tiers.keys()):
        if len(tiers[i]) > 0:
            pos = random.randint(0, len(tiers[i]) - 1)
            player = tiers[i].pop(pos)
            return player
    return None


def draft_teams(tiers, num_teams):
    """Draft players into teams using tier-based selection."""
    teams = [[] for _ in range(num_teams)]
    team_idx = 0
    while True:
        player = draft(tiers)
        if player is None:
            break
        teams[team_idx].append(player)
        team_idx = (team_idx + 1) % num_teams
    return teams


def main():
    """Main function to handle command line arguments and run the draft."""
    # Default values
    json_file = "players.json"
    num_teams = 3
    
    # Handle command line arguments
    if len(sys.argv) > 1:
        json_file = sys.argv[1]
    if len(sys.argv) > 2:
        try:
            num_teams = int(sys.argv[2])
            if num_teams < 1:
                print("Error: Number of teams must be at least 1.")
                sys.exit(1)
        except ValueError:
            print("Error: Number of teams must be a valid integer.")
            sys.exit(1)
    
    # Load players from JSON file
    tiers = load_players_from_json(json_file)
    
    # Print summary
    print_player_summary(tiers)
    
    # Draft teams
    teams = draft_teams(tiers, num_teams)
    
    # Display results
    for i, team in enumerate(teams, 1):
        print(f"Team {i}: {team}")


if __name__ == "__main__":
    main()
