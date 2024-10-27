package ubb.scs.map.service;

import org.jgrapht.Graph;
import org.jgrapht.alg.connectivity.ConnectivityInspector;
import org.jgrapht.graph.SimpleGraph;
import ubb.scs.map.domain.Friendship;
import ubb.scs.map.domain.Utilizator;
import ubb.scs.map.repository.InMemoryRepository;

import java.util.HashSet;
import java.util.List;
import java.util.Set;

import org.jgrapht.graph.DefaultEdge;

/**
 * Provides services for analyzing user communities based on friendships, including generating community graphs
 * and identifying the largest community.
 */
public class CommunityService {
    private final InMemoryRepository<Long, Utilizator> userRepository;
    private final InMemoryRepository<Long, Friendship> friendshipRepository;

    /**
     * Constructs a CommunityService with specified user and friendship repositories.
     *
     * @param userRepo repository for user data
     * @param friendshipRepo repository for friendship data
     */
    public CommunityService(InMemoryRepository<Long, Utilizator> userRepo, InMemoryRepository<Long, Friendship> friendshipRepo) {
        this.userRepository = userRepo;
        this.friendshipRepository = friendshipRepo;
    }

    /**
     * Builds a graph of communities, where each community is represented as a set of user IDs.
     *
     * @return a list of sets, each representing a connected community of users
     */
    public List<Set<Long>> getCommunityGraph() {
        Graph<Long, DefaultEdge> graph = new SimpleGraph<>(DefaultEdge.class);
        for(Utilizator user : userRepository.findAll()) {
            graph.addVertex(user.getId());
        }
        for(Friendship friendship : friendshipRepository.findAll()) {
            graph.addEdge(friendship.getFirstUser().getId(), friendship.getSecondUser().getId());
        }
        return new ConnectivityInspector<>(graph).connectedSets();
    }

    /**
     * Finds the largest community by the number of users.
     *
     * @return a set of user IDs representing the largest community
     */
    public Set<Long> biggestCommunity() {
        List<Set<Long>> communityGraph = getCommunityGraph();
        Set<Long> biggestCommunity = new HashSet<>();
        for(Set<Long> community : communityGraph) {
            if(community.size() > biggestCommunity.size()) {
                biggestCommunity=community;
            }
        }
        return biggestCommunity;
    }
}
