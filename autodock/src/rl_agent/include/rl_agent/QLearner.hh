/** \file
    Interface for an implementation of the canonical Q-learning
    algorithm. */

#ifndef _QLEARNER_HH_
#define _QLEARNER_HH_

#include <rl_common/Random.h>
#include <rl_common/core.hh>

#include <map>
#include <set>
#include <vector>

/** Agent that uses straight Q-learning, with no generalization and
    epsilon-greedy exploration. */
class QLearner: public Agent {
public:
  /** Standard constructor
      \param numactions The number of possible actions
      \param gamma The discount factor
      \param initialvalue The initial value of each Q(s,a)
      \param alpha The learning rate
      \param epsilon The probability of taking a random action
      \param rng Initial state of the random number generator to use */
  QLearner(int numactions, float gamma,
	   float initialvalue, float alpha, float epsilon,
	   Random rng = Random());

  /** Unimplemented copy constructor: internal state cannot be simply
      copied. */
  QLearner(const QLearner &);

  virtual ~QLearner();

  virtual int first_action(const std::vector<float> &s);
  virtual int next_action(float r, const std::vector<float> &s);
  virtual void last_action(float r);
  virtual void setDebug(bool d);
  virtual void seedExp(std::vector<experience>);
  virtual void savePolicy(const char* filename);
  void loadPolicy(const char* filename);

  void printState(const std::vector<float> &s);
  void printStateSpace(); 
  void printQ(); 
  float getValue(std::vector<float> state);
  
  std::vector<float>::iterator random_max_element(
						   std::vector<float>::iterator start,
						   std::vector<float>::iterator end);

  void logValues(ofstream *of, int xmin, int xmax, int ymin, int ymax);
  float epsilon;

protected:
  /** The implementation maps all sensations to a set of canonical
      pointers, which serve as the internal representation of
      environment state. */
  typedef const std::vector<float> *state_t;

  /** Produces a canonical representation of the given sensation.
      \param s The current sensation from the environment.
      \return A pointer to an equivalent state in statespace. */
  state_t canonicalize(const std::vector<float> &s);

private:
  /** Set of all distinct sensations seen.  Pointers to elements of
      this set serve as the internal representation of the environment
      state. */
  std::set<std::vector<float> > statespace;

  /** The primary data structure of the learning algorithm, the value
      function Q.  For state_t s and int a, Q[s][a] gives the
      learned maximum expected future discounted reward conditional on
      executing action a in state s. */
  std::map<state_t, std::vector<float> > Q;

  const int numactions;
  const float gamma;

  const float initialvalue;
  const float alpha;

  Random rng;
  float *currentq;

  bool ACTDEBUG;
};

#endif
