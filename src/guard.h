#ifndef __GUARD_H__
#define __GUARD_H__

void do_guard(P_char ch, char *argument, int cmd);
void guard_broken(struct char_link_data *cld);
bool is_being_guarded(P_char);
P_char guard_check(P_char attacker, P_char victim);
P_char guarded_by(P_char ch);
P_char guarding(P_char ch);


#endif // __GUARD_H__
