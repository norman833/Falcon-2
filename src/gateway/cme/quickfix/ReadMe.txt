Changes to QuickFix 1.14.3

1. FieldNumber.h
40c40
<     const int UserMin = 5000;
---
>     const int UserMin = 1;

2. Session.cpp
347a348,352
>   PossDupFlag possDupFlag(false);
>   resendRequest.getHeader().getFieldIfSet(possDupFlag);
>
>   if ( possDupFlag ) return;
>
655a661,668
>
>   SessionState::ResendRange range = m_state.resendRange();
>   if ( range.first == beginSeqNo )
>   {
>     m_state.onEvent( "Did not Send dup ResendRequest" );
>     return;
>   }
>