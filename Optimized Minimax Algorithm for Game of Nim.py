from functools import cache
import time
from itertools import combinations

choice_of_pile = 2

def possible_new_states(state):
    piles = []
    for i in range(len(state)):
        piles.append(i)
    possible_piles = list(combinations(piles, choice_of_pile))
    for pile in possible_piles:
        for remain in range(state[pile[0]]):
            yield state[: pile[0]] + (remain, ) + state[pile[0]+1: ]
        
        for remain in range(state[pile[1]]):                                #Needed for second choice
            yield state[: pile[1]] + (remain, ) + state[pile[1]+1: ]
            
        for remain1 in range(state[pile[0]]):                               #Needed for second choice
            for remain2 in range(state[pile[1]]):
                yield state[: pile[0]] + (remain1, ) + state[pile[0]+1: pile[1]] + (remain2, ) + state[pile[1]+1: ]

def evaluate(state, is_maximizing):
    if all(counters == 0 for counters in state):
        return -1 if is_maximizing else 1

@cache
def minimax(state, is_maximizing, alpha = -1, beta = 1):
    if (score := evaluate(state, is_maximizing)) is not None:
        return score
    
    # if is_maximizing:
    #     scores = [minimax(new_state, is_maximizing = False) for new_state in possible_new_states(state)]
    #     return max(scores)
    # else:
    #     scores = [minimax(new_state, is_maximizing = True) for new_state in possible_new_states(state)]
    #     return min(scores)
    
    scores = []
    for new_state in possible_new_states(state):
        scores.append(score := minimax(new_state, is_maximizing = not is_maximizing))
        if is_maximizing:
            alpha = max(alpha, score)
        else:
            beta = min(beta, score)
        if beta <= alpha:
            break
    
    return (max if is_maximizing else min)(scores)
    
    
def best_move(state):
    # for new_state in possible_new_states(state):
    #     score = minimax(new_state, is_maximizing = False)
    #     if score > 0:
    #         break
    # return score, new_state
    
    return max(
        (minimax(tuple(sorted(new_state)), is_maximizing = False), new_state) for new_state in possible_new_states(state))
    
start = time.time()

print(best_move((3, 4, 5)))

end = time.time()

print("\nExecution time: ", round((end - start), 3), "s")
