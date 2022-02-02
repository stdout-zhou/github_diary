import heapq
import subprocess


class JobNode(object):
    def __init__(self, id, name, command, max_execution_time, priority):
        self.id = id
        self.name = name
        self.command = command
        self.max_execution_time = max_execution_time
        self.priority = priority

    def __lt__(self, other):
        if not isinstance(other, JobNode):
            raise ValueError("Can not compare the two objects!")
        return self.priority < other.priority

    def execute(self):
        subprocess.check_output(self.command, timeout=self.max_execution_time)


class DagWorkflow(object):
    def __init__(self):
        self.job_set = set()
        self.dag_workflow = dict()
        self.node_in_degree = dict()

    def add_job(self, job_node):
        self.job_set.add(job_node)

    def add_dependency(self, source, target):
        # Target job has a dependency on source.
        if target in self.dag_workflow[source]:
            raise ValueError("The dependency from {} to {} has exist!".format(target, source))
        self.dag_workflow[source].add(target)
        self.node_in_degree[target] += 1

    def _is_dag(self):
        is_visit = {node: False for node in self.job_set}

        def _dfs(current_node):
            is_visit[current_node] = True
            for next_node in self.dag_workflow[current_node]:
                return not is_visit[next_node] and _dfs(next_node)

        for node in self.job_set:
            if is_visit:
                continue
            if not _dfs(node):
                return False
        return True

    def run(self):
        if not self._is_dag():
            raise ValueError("The workflow is not a dag!")
        ready_job_list = [node for node in self.job_set if self.node_in_degree[node] == 0]




