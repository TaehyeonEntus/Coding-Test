#include <string>
#include <vector>
#include <map>
using namespace std;

vector<string> solution(vector<string> players, vector<string> callings) {
    vector<string> answer;
    
    map<string, int> m_string;    //문자열로 현재 등수 찾기 MAP
    map<int, string> m_int;       //현재 등수로 문자열 찾기 MAP
    
    for(int i = 0; i<players.size(); i++){
        m_string[players[i]] = i;
        m_int[i] = players[i];
    }
    
    for(int i = 0; i<callings.size(); i++)
    {
        int second_index = m_string[callings[i]];       //second_index  추월할 선수 index
        string first_string = m_int[second_index-1];    //first_string 추월당할 선수 string
        
        m_int[second_index - 1] = callings[i];          //높은 등수의 이름은 추월한 선수
        m_int[second_index] = first_string;             //낮은 등수의 이름은 추월당한 선수
        
        m_string[callings[i]] = second_index - 1;       //추월한 선수를 높은 등수로
        m_string[first_string] = second_index;          //추월당한 선수를 낮은 등수로
    }
    
    for (pair<int, string> ans : m_int)
        answer.push_back(ans.second);   //문자열만 복사
    
    return answer;
}