# multiAgents.py
# --------------
# Licensing Information: Please do not distribute or publish solutions to this
# project. You are free to use and extend these projects for educational
# purposes. The Pacman AI projects were developed at UC Berkeley, primarily by
# John DeNero (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# For more info, see http://inst.eecs.berkeley.edu/~cs188/sp09/pacman.html

from util import manhattanDistance
from game import Directions
import random, util

from game import Agent

class ReflexAgent(Agent):
  """
    A reflex agent chooses an action at each choice point by examining
    its alternatives via a state evaluation function.

    The code below is provided as a guide.  You are welcome to change
    it in any way you see fit, so long as you don't touch our method
    headers.
  """


  def getAction(self, gameState):
    """
    You do not need to change this method, but you're welcome to.

    getAction chooses among the best options according to the evaluation function.

    Just like in the previous project, getAction takes a GameState and returns
    some Directions.X for some X in the set {North, South, West, East, Stop}
    """
    # Collect legal moves and successor states
    legalMoves = gameState.getLegalActions()

    # Choose one of the best actions
    scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
    bestScore = max(scores)
    bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
    chosenIndex = random.choice(bestIndices)  # Pick randomly among the best

    "Add more of your code here if you want to"

    return legalMoves[chosenIndex]

  def evaluationFunction(self, currentGameState, action):
    """
    Design a better evaluation function here.

    The evaluation function takes in the current and proposed successor
    GameStates (pacman.py) and returns a number, where higher numbers are better.

    The code below extracts some useful information from the state, like the
    remaining food (newFood) and Pacman position after moving (newPos).
    newScaredTimes holds the number of moves that each ghost will remain
    scared because of Pacman having eaten a power pellet.

    Print out these variables to see what you're getting, then combine them
    to create a masterful evaluation function.
    """
    # Useful information you can extract from a GameState (pacman.py)
    successorGameState = currentGameState.generatePacmanSuccessor(action)
    newPos = successorGameState.getPacmanPosition()
    newFood = currentGameState.getFood()
    newGhostStates = successorGameState.getGhostStates()
    newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]

    "*** YOUR CODE HERE ***"
    closestFood = float("inf")
    ghostForce  = 0  
     
    foodList = newFood.asList()
    
    for pos in foodList:
        d = manhattanDistance(newPos, pos)
        if d < closestFood:
            closestFood = d
    
    for ghost in newGhostStates:
        d = manhattanDistance(newPos, ghost.configuration.pos)
        
        if d == 0:
            return float("-inf")
        
        if d < 2:
            ghostForce = ghostForce + 0.25 / (d * d)
    
    if closestFood == 0:
        return float("inf")
    
    result = 1 + 0.5 / (closestFood * closestFood) - ghostForce
    return result

def scoreEvaluationFunction(currentGameState):
  """
    This default evaluation function just returns the score of the state.
    The score is the same one displayed in the Pacman GUI.

    This evaluation function is meant for use with adversarial search agents
    (not reflex agents).
  """
  return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
  """
    This class provides some common elements to all of your
    multi-agent searchers.  Any methods defined here will be available
    to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

    You *do not* need to make any changes here, but you can if you want to
    add functionality to all your adversarial search agents.  Please do not
    remove anything, however.

    Note: this is an abstract class: one that should not be instantiated.  It's
    only partially specified, and designed to be extended.  Agent (game.py)
    is another abstract class.
  """

  def __init__(self, evalFn='scoreEvaluationFunction', depth='2'):
    self.index = 0  # Pacman is always agent index 0
    self.evaluationFunction = util.lookup(evalFn, globals())
    self.depth = int(depth)

class MinimaxAgent(MultiAgentSearchAgent):
  """
    Your minimax agent (question 2)
  """

  def getAction(self, gameState):
    """
      Returns the minimax action from the current gameState using self.depth
      and self.evaluationFunction.

      Here are some method calls that might be useful when implementing minimax.

      gameState.getLegalActions(agentIndex):
        Returns a list of legal actions for an agent
        agentIndex=0 means Pacman, ghosts are >= 1

      Directions.STOP:
        The stop direction, which is always legal

      gameState.generateSuccessor(agentIndex, action):
        Returns the successor game state after an agent takes an action

      gameState.getNumAgents():
        Returns the total number of agents in the game
    """
    "*** YOUR CODE HERE ***"
    values     = {}
    legalMoves = gameState.getLegalActions(0)
    
    for action in legalMoves:
        nextState     = gameState.generateSuccessor(self.index, action)
        value         = self.minimax(nextState, self.index + 1, self.depth)
        values[value] = action
    
    return values[max(values)]

  def minimax(self, state, index, depth):
    result = 0
    
    if depth == 0 or state.isWin() or state.isLose():
        result = self.evaluationFunction(state)
    elif index == self.index:
        result = self.maximize(state, index, depth - 1)
    else:
        result = self.minimize(state, index, depth)

    return result
      
  def maximize(self, state, index, depth):
    result     = float("-inf")
    legalMoves = state.getLegalActions(index)

    for action in legalMoves:
        nextState = state.generateSuccessor(index, action)
        result    = max(result, self.minimax(nextState, (index + 1) % state.getNumAgents(), depth))
                  
    return result
      
  def minimize(self, state, index, depth):
    result     = float("inf")
    legalMoves = state.getLegalActions(index)
    
    for action in legalMoves:
        nextState = state.generateSuccessor(index, action)
        result    = min(result, self.minimax(nextState, (index + 1) % state.getNumAgents(), depth))          

    return result

class AlphaBetaAgent(MultiAgentSearchAgent):
  """
    Your minimax agent with alpha-beta pruning (question 3)
  """

  def getAction(self, gameState):
    """
      Returns the minimax action using self.depth and self.evaluationFunction
    """
    "*** YOUR CODE HERE ***"
    values     = {}
    legalMoves = gameState.getLegalActions(0)
    alpha      = float("-inf")
    
    for action in legalMoves:
        nextState     = gameState.generateSuccessor(self.index, action)
        value         = self.minimax(nextState, self.index + 1, self.depth, alpha, float("inf"))
        values[value] = action
        alpha         = max(alpha, value)
    
    return values[max(values)]

  def minimax(self, state, index, depth, alpha, beta):
    result = 0
    
    if depth == 0 or state.isWin() or state.isLose():
        result = self.evaluationFunction(state)
    elif index == self.index:
        result = self.maximize(state, index, depth - 1, alpha, beta)
    else:
        result = self.minimize(state, index, depth, alpha, beta)

    return result
      
  def maximize(self, state, index, depth, alpha, beta):
    result     = float("-inf")
    legalMoves = state.getLegalActions(index)

    if Directions.STOP in legalMoves:
        legalMoves.remove(Directions.STOP)

    for action in legalMoves:
        nextState = state.generateSuccessor(index, action)
        result    = max(result, self.minimax(nextState, (index + 1) % state.getNumAgents(), depth, alpha, beta))
        alpha     = max(alpha, result)
        if result >= beta:
            return result

    return result
      
  def minimize(self, state, index, depth, alpha, beta):
    result     = float("inf")
    legalMoves = state.getLegalActions(index)
    
    for action in legalMoves:
        nextState = state.generateSuccessor(index, action)
        result    = min(result, self.minimax(nextState, (index + 1) % state.getNumAgents(), depth, alpha, beta))          
        beta      = min(beta, result)
        if result <= alpha:
            return result

    return result

class ExpectimaxAgent(MultiAgentSearchAgent):
  """
    Your expectimax agent (question 4)
  """

  def getAction(self, gameState):
    """
      Returns the expectimax action using self.depth and self.evaluationFunction

      All ghosts should be modeled as choosing uniformly at random from their
      legal moves.
    """
    "*** YOUR CODE HERE ***"
    values     = {}
    legalMoves = gameState.getLegalActions(0)
    
    if Directions.STOP in legalMoves: 
        legalMoves.remove(Directions.STOP)
    
    for action in legalMoves:
        nextState     = gameState.generateSuccessor(self.index, action)
        value         = self.minimax(nextState, self.index + 1, self.depth)
        values[value] = action
    
    return values[max(values)]

  def minimax(self, state, index, depth):
    result = 0
    
    if depth == 0 or state.isWin() or state.isLose():
        result = self.evaluationFunction(state)
    elif index == self.index:
        result = self.maximize(state, index, depth - 1)
    else:
        result = self.expected(state, index, depth)

    return result
      
  def maximize(self, state, index, depth):
    result     = float("-inf")
    legalMoves = state.getLegalActions(index)

    legalMoves.remove(Directions.STOP)
    
    for action in legalMoves:
        nextState = state.generateSuccessor(index, action)
        result    = max(result, self.minimax(nextState, (index + 1) % state.getNumAgents(), depth))
                  
    return result
      
  def expected(self, state, index, depth):
    result     = 0
    legalMoves = state.getLegalActions(index)
    
    for action in legalMoves:
        nextState = state.generateSuccessor(index, action)
        result    = result + self.minimax(nextState, (index + 1) % state.getNumAgents(), depth)          

    return result/len(legalMoves)

def betterEvaluationFunction(currentGameState):
    """
      Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
      evaluation function (question 5).
    
      DESCRIPTION: model evaluation function as particules forces between pacman and food (attract ) or ghost (repel).
    """
    "*** YOUR CODE HERE ***"
    if currentGameState.isLose():
        return -9999999
    elif currentGameState.isWin(): 
        return 9999999    
      
    position     = currentGameState.getPacmanPosition()
    foodList     = currentGameState.getFood().asList()
    ghostStates  = currentGameState.getGhostStates()
    foodForce    = float("-inf")
    ghostsForce  = 0  
    foodCharge   = 2.0
    ghostsCharge = -8.0
    scaredCharge = 8.0
    
    for foodPos in foodList:
        d = manhattanDistance(position, foodPos)
        force = foodCharge/(d*d)
                
        if force > foodForce:
            foodForce = force
            
    for ghost in ghostStates:
        d = manhattanDistance(position, ghost.configuration.pos)
        
        if ghost.scaredTimer < d - 0.1:
            if d <= 2:
                return -9999999
            elif d <= 10:
                ghostsForce += ghostsCharge/(d*d)
        else:
            if d == 0:
                return 9999999
                
            ghostsForce += scaredCharge/(d*d)

    pacmanForce = currentGameState.getScore() + ghostsForce + foodForce
    return pacmanForce

# Abbreviation
better = betterEvaluationFunction

class ContestAgent(MultiAgentSearchAgent):
  """
    Your agent for the mini-contest
  """

  def getAction(self, gameState):
    """
      Returns an action.  You can use any method you want and search to any depth you want.
      Just remember that the mini-contest is timed, so you have to trade off speed and computation.

      Ghosts don't behave randomly anymore, but they aren't perfect either -- they'll usually
      just make a beeline straight towards Pacman (or away from him if they're scared!)
    """
    "*** YOUR CODE HERE ***"
    util.raiseNotDefined()

